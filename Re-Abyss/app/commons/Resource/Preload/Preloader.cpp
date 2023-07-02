#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Manager.hpp>
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
        LOAD_ASSET(vertexShader, Vs);
        LOAD_ASSET(pixelShader, Ps);
        LOAD_ASSET(audio, Audio);
        LOAD_ASSET(csv, CSV);
        LOAD_ASSET(toml, Toml);

        for (auto&& custom : m_info.custom) {
            custom(assets);
        }
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
        LOAD_ASSET(vertexShader, Vs);
        LOAD_ASSET(pixelShader, Ps);
        LOAD_ASSET(audio, Audio);
        LOAD_ASSET(csv, CSV);
        LOAD_ASSET(toml, Toml);

        for (auto&& custom : m_info.custom) {
            custom(assets);
            ++count;
            co_yield static_cast<double>(count) / static_cast<double>(loadNum);
        }
#undef LOAD_ASSET

#if ABYSS_DEBUG
        assets->setWarnMode(true);
#endif

        co_yield 1.0;
    }
    void Preloader::append(const s3d::String& preloadName)
    {
        this->m_info << Manager::GetInfo(preloadName);
    }
    Preloader& Preloader::operator<<(Preloader&& other)
    {
        this->m_info << std::move(other.m_info);
    }
}
