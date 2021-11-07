#include "OutLineShader.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    struct OutLineShaderParam
    {
        Float4 outlineColor;
        Float2 textureSize;
        float outlineSize;
        float _unused;
    };
}

namespace abyss
{
    class OutLineShader::Impl
    {
        PixelShader m_ps;
        ConstantBuffer<OutLineShaderParam> m_cb;

        Vec2 m_textureSize;
        double m_outlineSize = 1.0f;
        s3d::ColorF m_outlineColor;
    public:
        Impl() :
            m_ps(Resource::Assets::Norelease()->load(U"outline.hlsl"))
        {}

        void setTextureSize(const s3d::Vec2& size)
        {
            m_textureSize = size;
        }
        void setOutLineSize(double size)
        {
            m_outlineSize = size;
        }
        void setColor(const s3d::ColorF color)
        {
            m_outlineColor = color;
        }
        s3d::ScopedCustomShader2D start()
        {
            m_cb->textureSize = Float2(m_textureSize);
            m_cb->outlineSize = static_cast<float>(m_outlineSize);
            m_cb->outlineColor = m_outlineColor.toFloat4();
            Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, m_cb);
            return s3d::ScopedCustomShader2D(m_ps);
        }
    };
    OutLineShader::OutLineShader():
        m_pImpl(std::make_shared<Impl>())
    {}
    const OutLineShader& OutLineShader::setTextureSize(const s3d::Vec2 & size) const
    {
        m_pImpl->setTextureSize(size);
        return *this;
    }
    const OutLineShader& OutLineShader::setOutLineSize(double size) const
    {
        m_pImpl->setOutLineSize(size);
        return *this;
    }
    const OutLineShader& OutLineShader::setColor(const s3d::ColorF color) const
    {
        m_pImpl->setColor(color);
        return *this;
    }
    s3d::ScopedCustomShader2D OutLineShader::start() const
    {
        return m_pImpl->start();
    }
}
