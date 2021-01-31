#include "Manager.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Path.hpp>
#include <abyss/commons/Resource/Preload/PreloadInfo.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>
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

    s3d::Array<s3d::FilePath> GetPreloadFile()
    {
        s3d::Array<s3d::FilePath> ret;
#if ABYSS_NO_BUILD_RESOURCE
        for (auto& path : s3d::FileSystem::DirectoryContents(abyss::Path::PreloadPath)) {
            if (s3d::FileSystem::Extension(path) == U"json") {
                ret.push_back(s3d::FileSystem::RelativePath(path));
            }
        }
#else
        for (auto&& path : s3d::EnumResourceFiles()) {
            if (path.starts_with(U"RESOURCES/PRELOAD")) {
                ret.push_back(path);
            }
        }
#endif
        return ret;
    }
}

namespace abyss::Resource::Preload
{
    class Manager::Impl
    {
    public:
        Impl()
        {
            for (const auto& path : GetPreloadFile()) {
                JSONReader json(FileUtil::FixPath(path));
                if (!json) {
                    continue;
                }
                if (!json.isObject()) {
                    continue;
                }
                // リソースが大文字になっちゃうのでアッパーケースでキャッシュする
                auto fixName = path.uppercased();
#if ABYSS_DEBUG
                if (m_prelaodInfos.contains(fixName)) {
                    Debug::Log::PrintCache << U"Duplicated Load Preload File: {}"_fmt(fixName);
                }
#endif
                m_prelaodInfos.emplace(fixName, FromJson(json.objectView()));
            }
        }
    public:
        PreloadInfo getInfo(const s3d::String& preloadName)
        {
            // リソースが大文字になっちゃうのでアッパーケースでキャッシュする
            auto fixName = preloadName.uppercased();
            if (m_cache.contains(fixName)) {
                return m_cache[fixName];
            }
            // 先にインスタンス生成
            m_cache[fixName] = PreloadInfo{};

            PreloadInfo ret{};
            const auto& other = m_prelaodInfos[fixName];
            ret += other;
            for (const auto& p : other.preload) {
                ret += getInfo(p);
            }
            return m_cache[fixName] = ret.unique();
        }
    private:
        HashTable<String, PreloadInfoEx> m_prelaodInfos;
        HashTable<String, PreloadInfo> m_cache;
    };
    PreloadInfo Manager::GetInfo(const s3d::String& preloadName)
    {
        return Instance()->m_pImpl->getInfo(Path::PreloadPath + preloadName);
    }
    Manager::Manager():
        m_pImpl(std::make_unique<Impl>())
    {}
}
