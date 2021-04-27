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

        TileMapShader& setTextureSize(const Vec2& size);

        TileMapShader& setMapChip(const Texture& mapChip, const Vec2& tileSize);

        s3d::ScopedCustomShader2D start(Image&& image) const;
    };
}