#include "Manager.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Path.hpp>
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
}

namespace abyss::Resource::Preload
{
    Preloader::Preloader(const s3d::String& preloadName):
        m_info(Manager::GetInfo(preloadName))
    {

    }

    Preloader::Preloader(PreloadInfo&& info):
        m_info(std::move(info))
    {}

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
            return PreloadInfo{};
        }
    private:
        HashTable<String, PreloadInfoEx> m_prelaodInfos;
    };
    PreloadInfo Manager::GetInfo(const s3d::String& preloadName)
    {
        return Instance()->m_pImpl->getInfo(preloadName);
    }
    Manager::Manager():
        m_pImpl(std::make_unique<Impl>())
    {}
}
