#include "LightShader.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    struct ShaderParam
    {
        Float4 bgColor;
    };
    Image CreateDither()
    {
        Image image(4, 4);
        constexpr double dither[4][4] = {
            {1, 13, 4, 16},
            {9, 5, 12, 8},
            {3, 15, 2, 14},
            {11, 7, 10, 6},
        };
        for (int32 y : step(0, 4)) {
            for (int32 x : step(0, 4)) {
                image[y][x] = ColorF(dither[y][x] / 17.0);
            }
        }
        return image;
    }
}

namespace abyss
{
    class LightShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Main()->load(U"light.hlsl")),
            m_dither(::CreateDither())
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
            s3d::Graphics2D::SetTexture(1, m_dither);
            s3d::Graphics2D::SetTexture(2, m_lights);
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
        m_pImpl(std::make_shared<Impl>())
    {}
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