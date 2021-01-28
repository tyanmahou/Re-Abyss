#pragma once
#include <Siv3D/JSONReader.hpp>
#include <Siv3D/Array.hpp>
#include <abyss/utils/Singleton.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/utils/Coro/Generator/Generator.hpp>

namespace abyss::Resource::Preload
{
    struct PreloadInfo
    {
        s3d::Array<s3d::String> texture;
        s3d::Array<s3d::String> texturePacker;
        s3d::Array<s3d::String> tmx;
        s3d::Array<s3d::String> pixelShader;
        s3d::Array<s3d::String> audio;
        s3d::Array<s3d::String> audioSetting;
        s3d::Array<s3d::String> toml;

        PreloadInfo& unique();

        PreloadInfo& operator +=(const PreloadInfo& other);
    };

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

    class Manager final : protected Singleton<Manager>
    {
        friend class Singleton<Manager>;
    public:
        static PreloadInfo GetInfo(const s3d::String& preloadName);
    private:
        Manager();
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
}