#pragma once
#include <abyss/commons/Resource/Preload/PreloadInfo.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/utils/Coro/Generator/Generator.hpp>

namespace abyss::Resource::Preload
{
    class Preloader
    {
    public:
        Preloader() = default;
        Preloader(const s3d::String& preloadName);

        Preloader(PreloadInfo&& info);

        Coro::Generator<double> preloadProgress(const Assets* assets = Assets::Main()) const;
    private:
        PreloadInfo m_info;
    };
}