#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Resource::Preload
{
    /// <summary>
    /// プリロード情報
    /// </summary>
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
        size_t size() const;

        PreloadInfo& operator +=(const PreloadInfo& other);
    };

    using PreloadInfoMemPtr = decltype(&PreloadInfo::texture);
    inline constexpr PreloadInfoMemPtr PrelaodInfoMemPtrs[]{
        &PreloadInfo::texture,
        &PreloadInfo::texturePacker,
        &PreloadInfo::tmx,
        &PreloadInfo::pixelShader,
        &PreloadInfo::audio,
        &PreloadInfo::audioSetting,
        &PreloadInfo::toml
    };
}
