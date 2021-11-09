#include "Preloader.hpp"
#include <abyss/commons/Resource/Preload/Manager.hpp>
#include <abyss/utils/AudioSetting/AudioSettingGroup.hpp>
#include <S3DTiled.hpp>

namespace abyss::Resource::Preload
{
    Preloader::Preloader(const s3d::String& preloadName) :
        m_info(Manager::GetInfo(preloadName))
    {}

    Preloader::Preloader(PreloadInfo&& info) :
        m_info(std::move(info))
    {}

    void Preloader::preload(const Assets* assets)
    {
#if ABYSS_DEBUG
        assets->setWarnMode(false);
#endif
#define LOAD_ASSET(a, b, ...)\
        for (const auto& path : m_info.##a) {\
            [[maybe_unused]]auto&& it =  assets->load##b(path);\
            __VA_ARGS__\
        }

        LOAD_ASSET(texture, Texture);
        LOAD_ASSET(texturePacker, TexturePacker);
        LOAD_ASSET(tmx, Tmx);
        LOAD_ASSET(pixelShader, Ps);
        LOAD_ASSET(audio, Audio);
        LOAD_ASSET(audioSettingGroup, AudioSettingGroup, {
            for (const auto& [key, as] : it) {
                assets->loadAudio(as);
            }
        });
        LOAD_ASSET(toml, Toml);

#undef LOAD_ASSET
#if ABYSS_DEBUG
        assets->setWarnMode(true);
#endif
    }

    Coro::Generator<double> Preloader::preloadProgress(const Assets* assets) const
    {
#if ABYSS_DEBUG
        assets->setWarnMode(false);
#endif
        size_t loadNum = m_info.size();
        size_t count = 0;
#define LOAD_ASSET(a, b, ...)\
        for (const auto& path : m_info.##a) {\
            [[maybe_unused]]auto&& it = assets->load##b(path);\
            __VA_ARGS__\
            ++count;\
            co_yield static_cast<double>(count) / static_cast<double>(loadNum);\
        }

        LOAD_ASSET(texture, Texture);
        LOAD_ASSET(texturePacker, TexturePacker);
        LOAD_ASSET(tmx, Tmx);
        LOAD_ASSET(pixelShader, Ps);
        LOAD_ASSET(audio, Audio);
        LOAD_ASSET(audioSettingGroup, AudioSettingGroup, {
            for (const auto& [key, as] : it) {
                assets->loadAudio(as);
            }
        });
        LOAD_ASSET(toml, Toml);

#undef LOAD_ASSET

#if ABYSS_DEBUG
        assets->setWarnMode(true);
#endif

        co_yield 1.0;
    }
}