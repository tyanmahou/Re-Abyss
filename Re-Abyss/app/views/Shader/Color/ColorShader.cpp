#include <abyss/views/Shader/Color/ColorShader.hpp>
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
    class ColorShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Norelease()->load(U"color.hlsl"))
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
    ColorShader::ColorShader() :
        m_pImpl(std::make_unique<Impl>())
    {
    }

    ColorShader& ColorShader::setColor(const s3d::ColorF& color)
    {
        m_pImpl->setColor(color);
        return *this;
    }

    s3d::ScopedCustomShader2D ColorShader::start() const
    {
        return m_pImpl->start();
    }
}
