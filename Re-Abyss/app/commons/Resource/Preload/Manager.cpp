#include "Manager.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Path.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>
#include <abyss/utils/AudioSetting/AudioSettingGroup.hpp>
#include <S3DTiled.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace 
{
    using namespace abyss::Resource::Preload;

    struct PreloadInfoEx : PreloadInfo
    {
        s3d::Array<s3d::String> preload;
    };
    PreloadInfoEx FromJson(const s3d::JSONObjectView& json)
    {
        PreloadInfoEx ret;
        for (const auto& [name, value] : json) {
            if (name == U"Preload") {
                ret.preload = value.getArray<s3d::String>();
            } else if (name == U"Texture") {
                ret.texture = value.getArray<s3d::String>();
            } else if (name == U"TexturePacker") {
                ret.texturePacker = value.getArray<s3d::String>();
            } else if (name == U"Tmx") {
                ret.tmx = value.getArray<s3d::String>();
            } else if (name == U"PixelShader") {
                ret.pixelShader = value.getArray<s3d::String>();
            } else if (name == U"Audio") {
                ret.audio = value.getArray<s3d::String>();
            } else if (name == U"AudioSetting") {
                ret.audioSetting = value.getArray<s3d::String>();
            } else if (name == U"Audio") {
                ret.audio = value.getArray<s3d::String>();
            } else if (name == U"Toml") {
                ret.toml = value.getArray<s3d::String>();
            }
        }
        return ret;
    }

    using PreloadInfoMemPtr = decltype(&PreloadInfo::texture);
    constexpr PreloadInfoMemPtr g_prelaodInfoMemPtrs[]{
        &PreloadInfo::texture,
        &PreloadInfo::texturePacker,
        &PreloadInfo::tmx,
        &PreloadInfo::pixelShader,
        &PreloadInfo::audio,
        &PreloadInfo::audioSetting,
        &PreloadInfo::toml
    };
}

namespace abyss::Resource::Preload
{
    PreloadInfo& PreloadInfo::unique()
    {
        for (auto&& memP : g_prelaodInfoMemPtrs) {
            (this->*memP).unique();
        }
        return *this;
    }
    PreloadInfo& PreloadInfo::operator+=(const PreloadInfo& other)
    {
        for (auto&& memP : g_prelaodInfoMemPtrs) {
            (this->*memP).append(other.*memP);
        }
    }
    Preloader::Preloader(const s3d::String& preloadName):
        m_info(Manager::GetInfo(preloadName))
    {

    }

    Preloader::Preloader(PreloadInfo&& info):
        m_info(std::move(info))
    {}

    Coro::Generator<double> Preloader::preloadProgress(const Assets * assets) const
    {
        uint32 loadNum = 0;
        for (auto&& memP : g_prelaodInfoMemPtrs) {
            loadNum += (m_info.*memP).size();
        }
        uint32 count = 0;
#define LOAD_ASSET(a, b)\
        for (const auto& path : m_info.##a) {\
            assets->load##b(path);\
            ++count;\
            co_yield static_cast<double>(count) / static_cast<double>(loadNum);\
        }

        LOAD_ASSET(texture, Texture);
        LOAD_ASSET(texturePacker, TexturePacker);
        LOAD_ASSET(tmx, Tmx);
        LOAD_ASSET(pixelShader, Audio);
        LOAD_ASSET(audio, Texture);
        LOAD_ASSET(audioSetting, AudioSettingGroup);
        LOAD_ASSET(toml, Toml);

#undef LOAD_ASSET
        co_yield 1.0;
    }

    class Manager::Impl
    {
    public:
        Impl()
        {
            s3d::Array<s3d::FilePathView> paths{
                U"Cycle/splash.json",
            };

            for (const auto& preloadPath : paths) {
                JSONReader json(FileUtil::FixPath(Path::PreloadPath + preloadPath));
                if (!json) {
                    continue;
                }
                if (!json.isObject()) {
                    continue;
                }
                for (const auto& [name, value] : json.objectView()) {
                    if (!value.isObject()) {
                        continue;
                    }
#if ABYSS_DEBUG
                    if (m_prelaodInfos.contains(name)) {
                        Debug::Log::PrintCache << U"Duplicated Preload Name: {}"_fmt(name);
                    }
#endif
                    m_prelaodInfos.emplace(name, FromJson(value.objectView()));
                }
            }
        }
    public:
        PreloadInfo getInfo(const s3d::String& preloadName)
        {
            if (m_cache.contains(preloadName)) {
                return m_cache[preloadName];
            }
            // 先にインスタンス生成
            m_cache[preloadName] = PreloadInfo{};

            PreloadInfo ret{};
            const auto& other = m_prelaodInfos[preloadName];
            ret += other;
            for (const auto& p : other.preload) {
                ret += getInfo(p);
            }
            return m_cache[preloadName] = ret.unique();
        }
    private:
        HashTable<String, PreloadInfoEx> m_prelaodInfos;
        HashTable<String, PreloadInfo> m_cache;
    };
    PreloadInfo Manager::GetInfo(const s3d::String& preloadName)
    {
        return Instance()->m_pImpl->getInfo(preloadName);
    }
    Manager::Manager():
        m_pImpl(std::make_unique<Impl>())
    {}
}
