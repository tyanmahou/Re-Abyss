#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
namespace abyss::Decor::Map
{
    /// <summary>
    /// TileMapShader
    /// </summary>
    class TileMapShader
    {
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    public:
        TileMapShader();

        TileMapShader& setTextureSize(const s3d::Vec2& size);

        TileMapShader& setMapChip(const s3d::Texture& mapChip, const s3d::Vec2& tileSize);

        s3d::ScopedCustomShader2D start(s3d::Image&& image) const;
    };
}