#include "Manager.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Path.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>

#include <abyss/debugs/Log/Log.hpp>

namespace
{
    /// <summary>
    /// プリロード情報
    /// </summary>
    struct PreloadInfo
    {
        s3d::Array<s3d::String> preload;
        s3d::Array<s3d::String> texture;
        s3d::Array<s3d::String> texturePacker;
        s3d::Array<s3d::String> tmx;
        s3d::Array<s3d::String> pixelShader;
        s3d::Array<s3d::String> audio;
        s3d::Array<s3d::String> audioSetting;
        s3d::Array<s3d::String> toml;

        PreloadInfo(const s3d::JSONObjectView& json)
        {
            for (const auto& [name, value] : json) {
                if (name == U"Preload") {
                    preload = value.getArray<s3d::String>();
                } else if (name == U"Texture") {
                    texture = value.getArray<s3d::String>();
                } else if (name == U"TexturePacker") {
                    texturePacker = value.getArray<s3d::String>();
                } else if (name == U"Tmx") {
                    tmx = value.getArray<s3d::String>();
                } else if (name == U"PixelShader") {
                    pixelShader = value.getArray<s3d::String>();
                } else if (name == U"Audio") {
                    audio = value.getArray<s3d::String>();
                } else if (name == U"AudioSetting") {
                    audioSetting = value.getArray<s3d::String>();
                } else if (name == U"Audio") {
                    audio = value.getArray<s3d::String>();
                } else if (name == U"Toml") {
                    toml = value.getArray<s3d::String>();
                }
            }
        }
    };
}
namespace abyss::Resource::Preload
{
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
                for (auto&& [name, value] : json.objectView()) {
                    if (!value.isObject()) {
                        continue;
                    }
#if ABYSS_DEBUG
                    if (m_prelaodInfos.contains(name)) {
                        Debug::Log::PrintCache << U"Duplicated Preload Name: {}"_fmt(name);
                    }
#endif
                    m_prelaodInfos.emplace(name, value.objectView());
                }
            }
        }
    private:
        HashTable<String, PreloadInfo> m_prelaodInfos;
    };
    Manager::Manager():
        m_pImpl(std::make_unique<Impl>())
    {}
}
