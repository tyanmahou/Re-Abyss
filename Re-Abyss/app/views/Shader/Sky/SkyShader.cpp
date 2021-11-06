#include "SkyShader.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    struct SkyShaderParam
    {
        float timer;
        float multiply;
        float _unused[2];
    };
}
namespace abyss
{
    class SkyShader::Impl
    {
        PixelShader m_ps;
        ConstantBuffer<SkyShaderParam> m_cb;
        double m_multiply = 1.0f;
        double m_time = 0.0;
    public:
        Impl() :
            m_ps(Resource::Assets::Main()->load(U"sky.hlsl"))
        {}

        void setMultiply(double multiply)
        {
            m_multiply = multiply;
        }
        void setTime(double time)
        {
            m_time = time;
        }
        ScopedCustomShader2D start()
        {
            m_cb->timer = static_cast<float>(m_time);
            m_cb->multiply = static_cast<float>(m_multiply);
            Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, m_cb);
            return ScopedCustomShader2D(m_ps);
        }

    };
    SkyShader::SkyShader() :
        m_pImpl(std::make_shared<Impl>())
    {}

    SkyShader& SkyShader::setTime(double time)
    {
        m_pImpl->setTime(time);
        return *this;
    }

    const SkyShader& SkyShader::setMultiply(double multiply) const
    {
        m_pImpl->setMultiply(multiply);
        return *this;
    }

    ScopedCustomShader2D SkyShader::start() const
    {
        return m_pImpl->start();
    }
}
