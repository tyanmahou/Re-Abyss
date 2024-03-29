#include <abyss/views/Shader/TileMap/TileMapShader.hpp>

#include <abyss/commons/Resource/Assets/Assets.hpp>

#include <Siv3D.hpp>

namespace
{
    struct TileMapShaderParam
    {
        Float2 textureSize;
        Float2 mapChipSize;
        Float2 mapChipGIdSize;
        Float2 tileSize;
    };
}
namespace abyss
{
    class TileMapShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::NoRelease()->load(U"tilemap.hlsl"))
        {}

        void setTextureSize(const Vec2& size)
        {
            m_cb->textureSize = size;
        }

        void setMapChip(const Texture& mapChip, const Vec2& tileSize)
        {
            m_mapChip = mapChip;
            m_cb->mapChipSize = mapChip.size();
            m_cb->mapChipGIdSize = mapChip.size() / tileSize;
            m_cb->tileSize = tileSize;
        }
        s3d::ScopedCustomShader2D start(Image&& image)
        {
            m_gId.fill(std::move(image));
            s3d::Graphics2D::SetPSTexture(1, m_mapChip);
            s3d::Graphics2D::SetPSTexture(2, m_gId);
            s3d::Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, m_cb);
            return s3d::ScopedCustomShader2D(m_ps);
        }
    private:
        Texture m_mapChip;
        DynamicTexture m_gId;

        PixelShader m_ps;
        ConstantBuffer<TileMapShaderParam> m_cb;
    };
    TileMapShader::TileMapShader():
        m_pImpl(std::make_unique<Impl>())
    {}
    TileMapShader::~TileMapShader()
    {
    }
    TileMapShader& TileMapShader::setTextureSize(const Vec2 & size)
    {
        m_pImpl->setTextureSize(size);
        return *this;
    }
    TileMapShader& TileMapShader::setMapChip(const Texture& mapChip, const Vec2& tileSize)
    {
        m_pImpl->setMapChip(mapChip, tileSize);
        return *this;
    }
    s3d::ScopedCustomShader2D TileMapShader::start(Image&& image) const
    {
        return m_pImpl->start(std::move(image));
    }
}
