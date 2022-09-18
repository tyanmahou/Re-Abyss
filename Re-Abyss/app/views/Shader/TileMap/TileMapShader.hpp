#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    /// <summary>
    /// TileMapShader
    /// </summary>
    class TileMapShader
    {
    public:
        TileMapShader();
        ~TileMapShader();

        TileMapShader& setTextureSize(const s3d::Vec2& size);

        TileMapShader& setMapChip(const s3d::Texture& mapChip, const s3d::Vec2& tileSize);

        s3d::ScopedCustomShader2D start(s3d::Image&& image) const;
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
}
