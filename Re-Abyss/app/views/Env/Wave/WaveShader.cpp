#include "WaveShader.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    struct WaveParam
    {
        float width;
        float height;
        float timer;
        float multiply;
    };
}
namespace abyss::Env
{
    class WaveShader::Impl
    {
        RenderTexture m_rt;
        PixelShader m_ps;
        ConstantBuffer<WaveParam> m_cb;
        float m_timer = 0.0f;
        float m_multiply = 2.0f;
    public:
        Impl() :
            m_rt(static_cast<uint32>(Constants::GameScreenSize.x), static_cast<uint32>(Constants::GameScreenSize.y)),
            m_ps(Resource::Assets::Main()->loadPs(U"wave.hlsl"))
        {}

        void setTimer(double timer)
        {
            m_timer = static_cast<float>(timer);
        }
        void setMultiply(float multiply)
        {
            m_multiply = multiply;
        }
        void apply(std::function<void()> drawer)
        {
            m_rt.clear(ColorF(0.0, 1.0));
            {
                ScopedRenderTarget2D target(m_rt);
                drawer();
            }
            {
                ScopedRenderStates2D state(SamplerState::Default2D);
                auto shader = this->start();
                Transformer2D t2dIdenty(Mat3x2::Identity(), s3d::Transformer2D::Target::SetLocal);
                m_rt.draw();
            }

        }
        ScopedCustomShader2D start()
        {
            constexpr auto ScreenSizeF = Constants::GameScreenSize_v<float>;
            m_cb->width = ScreenSizeF.x;
            m_cb->height = ScreenSizeF.y;
            m_cb->timer = m_timer;
            m_cb->multiply = m_multiply;
            Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, m_cb);
            return ScopedCustomShader2D(m_ps);
        }

    };
    WaveShader::WaveShader() :
        m_pImpl(std::make_shared<Impl>())
    {}

    const WaveShader& WaveShader::setTime(double time) const
    {
        m_pImpl->setTimer(time);
        return *this;
    }

    const WaveShader& WaveShader::setMultiply(float multiply)const
    {
        m_pImpl->setMultiply(multiply);
        return *this;
    }

    ScopedCustomShader2D WaveShader::start() const
    {
        return m_pImpl->start();
    }

    void WaveShader::apply(std::function<void()> drawer) const
    {
        m_pImpl->apply(drawer);
    }

}

