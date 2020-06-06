#include "SkyShader.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

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
        float m_multiply = 1.0f;
    public:
        Impl() :
            m_ps(ResourceManager::Main()->loadPs(U"sky.hlsl"))
        {}

        void setMultiply(float multiply)
        {
            m_multiply = multiply;
        }
        ScopedCustomShader2D start()
        {
            m_cb->timer = static_cast<float>(Scene::Time());
            m_cb->multiply = m_multiply;
            Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, m_cb);
            return ScopedCustomShader2D(m_ps);
        }

    };
    SkyShader::SkyShader() :
        m_pImpl(std::make_shared<Impl>())
    {}

    ScopedCustomShader2D abyss::SkyShader::start() const
    {
        return m_pImpl->start();
    }
}
