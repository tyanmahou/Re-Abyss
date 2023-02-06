#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Resource
{
    class Assets;
}
namespace abyss::Resource::Preload
{
    using CustomPreload = std::function<void(const Assets*)>;

    /// <summary>
    /// プリロード情報
    /// </summary>
    struct PreloadInfo
    {
        s3d::Array<s3d::FilePath> texture;
        s3d::Array<s3d::FilePath> texturePacker;
        s3d::Array<s3d::FilePath> tmx;
        s3d::Array<s3d::FilePath> vertexShader;
        s3d::Array<s3d::FilePath> pixelShader;
        s3d::Array<s3d::FilePath> audio;
        s3d::Array<s3d::FilePath> audioSettingGroup;
        s3d::Array<s3d::FilePath> toml;
        s3d::Array<CustomPreload> custom;

        PreloadInfo& unique();
        size_t size() const;

        PreloadInfo& operator <<(const PreloadInfo& other);
        PreloadInfo& operator <<(PreloadInfo&& other);
    };

    using PreloadInfoMemPtr = decltype(&PreloadInfo::texture);
    inline constexpr PreloadInfoMemPtr PrelaodInfoMemPtrs[]{
        &PreloadInfo::texture,
        &PreloadInfo::texturePacker,
        &PreloadInfo::tmx,
        &PreloadInfo::vertexShader,
        &PreloadInfo::pixelShader,
        &PreloadInfo::audio,
        &PreloadInfo::audioSettingGroup,
        &PreloadInfo::toml
    };
}
