#include <abyss/views/Shader/Blend/BlendShader.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace
{
    struct ShaderParam
    {
        Float4 color;
        abyss::BlendMode mode;
    };
}

namespace abyss
{
    class BlendShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::NoRelease()->load(U"blend.hlsl"))
        {}
        void setColor(const s3d::ColorF& color)
        {
            m_cb->color = color.toFloat4();
        }
        void setBlendMode(BlendMode mode)
        {
            m_cb->mode = mode;
        }
        ScopedCustomShader2D start() const
        {
            s3d::Graphics2D::SetConstantBuffer(s3d::ShaderStage::Pixel, 1, m_cb);
            return ScopedCustomShader2D(m_ps);
        }
    private:
        PixelShader m_ps;
        ConstantBuffer<ShaderParam> m_cb;
    };
    BlendShader::BlendShader() :
        m_pImpl(std::make_unique<Impl>())
    {
    }

    BlendShader::~BlendShader()
    {
    }

    const BlendShader& BlendShader::setColor(const s3d::ColorF& color) const
    {
        m_pImpl->setColor(color);
        return *this;
    }

    const BlendShader& BlendShader::setBlendMode(BlendMode mode) const
    {
        m_pImpl->setBlendMode(mode);
        return *this;
    }

    s3d::ScopedCustomShader2D BlendShader::start() const
    {
        return m_pImpl->start();
    }
}
