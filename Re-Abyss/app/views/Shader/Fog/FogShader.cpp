#include <abyss/views/Shader/Fog/FogShader.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace
{
    struct FogParam
    {
        Float4 fogColor;
        float fogFactor;
        float z;
    };
}

namespace abyss
{
    class FogShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Norelease()->load(U"fog.hlsl"))
        {
            m_cb->z = 0;
            m_cb->fogFactor = 1.0;
            m_cb->fogColor = ColorF(Color(150, 200, 255, 255)).toFloat4();
        }

        void setFogColor(const s3d::ColorF& color)
        {
            m_cb->fogColor = color.toFloat4();
        }

        void setFogFactor(double factor)
        {
            m_cb->fogFactor = static_cast<float>(factor);
        }

        void setZ(double z)
        {
            m_cb->z = static_cast<float>(s3d::Saturate(z));
        }
        ScopedCustomShader2D start() const
        {
            s3d::Graphics2D::SetConstantBuffer(s3d::ShaderStage::Pixel, 1, m_cb);
            return ScopedCustomShader2D(m_ps);
        }
    private:
        PixelShader m_ps;
        ConstantBuffer<FogParam> m_cb;
    };

    FogShader::FogShader():
        m_pImpl(std::make_shared<Impl>())
    {
    }

    const FogShader& FogShader::setFogColor(const s3d::ColorF& color) const
    {
        m_pImpl->setFogColor(color);
        return *this;
    }

    const FogShader& FogShader::setFogFactor(double factor) const
    {
        m_pImpl->setFogFactor(factor);
        return *this;
    }

    const FogShader& FogShader::setZ(double z) const
    {
        m_pImpl->setZ(z);
        return *this;
    }

    s3d::ScopedCustomShader2D FogShader::start() const
    {
        return m_pImpl->start();
    }

}
