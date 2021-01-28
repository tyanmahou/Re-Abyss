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

    Coro::Generator<double> Preloader::preloadProgress(const Assets* assets) const
    {
        size_t loadNum = m_info.size();
        size_t count = 0;
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
}