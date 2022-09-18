#include <abyss/views/Shader/Blend/BlendShader.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace
{
    struct ShaderParam
    {
        Float4 color;
    };
}

namespace abyss
{
    class BlendShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Norelease()->load(U"blend.hlsl"))
        {}
        void setColor(const s3d::ColorF& color)
        {
            m_cb->color = color.toFloat4();
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

    s3d::ScopedCustomShader2D BlendShader::start() const
    {
        return m_pImpl->start();
    }
}
