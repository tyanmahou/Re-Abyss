#include "WaveShader.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/views/Camera/CameraView.hpp>

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
namespace abyss
{
    class WaveShader::Impl
    {
        RenderTexture m_rt;
        PixelShader m_ps;
        ConstantBuffer<WaveParam> m_cb;
        float m_multiply = 2.0f;
    public:
        Impl() :
            m_rt(static_cast<uint32>(Constants::GameScreenSize.x), static_cast<uint32>(Constants::GameScreenSize.y)),
            m_ps(Resource::Assets::Main()->loadPs(U"wave.hlsl"))
        {}

        void setMultiply(float multiply)
        {
            m_multiply = multiply;
        }
        void apply(const CameraView& camera, std::function<void()> drawer)
        {
            m_rt.clear(ColorF(0.0, 1.0));
            {
                ScopedRenderTarget2D target(m_rt);
                Transformer2D t2d(Mat3x2::Translate({ 0, -20.0f }), Transformer2D::Target::PushLocal);
                drawer();
            }
            {
                ScopedRenderStates2D state(SamplerState::Default2D);
                auto shader = this->start();
                m_rt.draw(camera.screenRegion().pos);
            }

        }
        ScopedCustomShader2D start()
        {
            constexpr auto ScreenSizeF = Constants::GameScreenSize_v<float>;
            m_cb->width = ScreenSizeF.x;
            m_cb->height = ScreenSizeF.y;
            m_cb->timer = static_cast<float>(Scene::Time());
            m_cb->multiply = m_multiply;
            Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, m_cb);
            return ScopedCustomShader2D(m_ps);
        }

    };
    WaveShader::WaveShader() :
        m_pImpl(std::make_shared<Impl>())
    {}

    const WaveShader& WaveShader::setMultiply(float multiply)const
    {
        m_pImpl->setMultiply(multiply);
        return *this;
    }

    ScopedCustomShader2D WaveShader::start() const
    {
        return m_pImpl->start();
    }

    void WaveShader::apply(const CameraView& camera, std::function<void()> drawer) const
    {
        m_pImpl->apply(camera, drawer);
    }

}

