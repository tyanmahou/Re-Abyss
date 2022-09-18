#include <abyss/views/Shader/Light/LightShader.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/views/Shader/util/BayerMatrix.hpp>
#include <Siv3D.hpp>

namespace
{
    struct ShaderParam
    {
        Float4 bgColor;
    };
}

namespace abyss
{
    class LightShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Norelease()->load(U"light.hlsl")),
            m_dither(BayerMatrix::Texture())
        {}
        void setBgColor(const s3d::ColorF& color)
        {
            m_cb->bgColor = color.toFloat4();
        }
        void setLightsTexture(const s3d::Texture& lights)
        {
            m_lights = lights;
        }
        ScopedCustomShader2D start() const
        {
            s3d::Graphics2D::SetPSTexture(1, m_dither);
            s3d::Graphics2D::SetPSTexture(2, m_lights);
            s3d::Graphics2D::SetConstantBuffer(s3d::ShaderStage::Pixel, 1, m_cb);
            return ScopedCustomShader2D(m_ps);
        }
    private:
        PixelShader m_ps;
        ConstantBuffer<ShaderParam> m_cb;
        s3d::Texture m_dither;
        s3d::Texture m_lights;
    };
    LightShader::LightShader():
        m_pImpl(std::make_unique<Impl>())
    {}
    LightShader::~LightShader()
    {
    }
    const LightShader& LightShader::setBgColor(const s3d::ColorF & color) const
    {
        m_pImpl->setBgColor(color);
        return *this;
    }
    const LightShader& LightShader::setLightsTexture(const s3d::Texture& lights) const
    {
        m_pImpl->setLightsTexture(lights);
        return *this;
    }
    s3d::ScopedCustomShader2D LightShader::start() const
    {
        return m_pImpl->start();
    }
}
