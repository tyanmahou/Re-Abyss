#include "WaveShader.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/views/Camera/CameraView.hpp>

namespace
{
    struct WaveParam
    {
        float width;
        float height;
        float timer;
        float _unused;
    };
}
namespace abyss
{
    class WaveShader::Impl
    {
        RenderTexture m_rt;
        PixelShader m_ps;
        ConstantBuffer<WaveParam> m_cb;
    public:
        Impl() :
            m_rt(static_cast<uint32>(Constants::GameScreenSize.x), static_cast<uint32>(Constants::GameScreenSize.y)),
            m_ps(U"resources/shaders/wave.hlsl", { { U"PSConstants2D", 0 } })
        {}

        void apply(const CameraView& camera, std::function<void()> drawer)
        {
            m_rt.clear(ColorF(0.0, 1.0));
            {
                ScopedRenderTarget2D target(m_rt);
                Transformer2D t2d(Mat3x2::Translate({ 0, -20.0f }), Transformer2D::Target::PushLocal);
                drawer();
            }
            {
                m_cb->width = static_cast<float>(Constants::GameScreenSize.x);
                m_cb->height = static_cast<float>(Constants::GameScreenSize.y);
                m_cb->timer = static_cast<float>(Scene::Time());
                Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, m_cb);
                ScopedCustomShader2D shader(m_ps);
                m_rt.draw(camera.screenRegion().pos);
            }

        }


    };
    WaveShader::WaveShader() :
        m_pImpl(std::make_shared<Impl>())
    {}

    void WaveShader::apply(const CameraView& camera, std::function<void()> drawer) const
    {
        m_pImpl->apply(camera, drawer);
    }

}

