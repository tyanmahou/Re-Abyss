#include "LightView.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    struct ShaderParam
    {
        Float2 size;
        float _unused[2];
    };
}

namespace abyss
{
    class LightShader
    {
    public:
        LightShader():
            m_ps(Resource::Assets::Main()->loadPs(U"light.hlsl"))
        {

        }
        
        LightShader& setSize(const Size& size)
        {
            m_cb->size = static_cast<Float2>(size);
            return *this;
        }
        ScopedCustomShader2D start()
        {
            s3d::Graphics2D::SetConstantBuffer(s3d::ShaderStage::Pixel, 1, m_cb);
            return ScopedCustomShader2D(m_ps);
        }
    private:
        PixelShader m_ps;
        ConstantBuffer<ShaderParam> m_cb;
    };

    LightView::LightView():
        m_rt(Constants::GameScreenSize_v<uint32>.x, Constants::GameScreenSize_v<uint32>.y),
        m_rt2(Constants::GameScreenSize_v<uint32>.x, Constants::GameScreenSize_v<uint32>.y),
        m_shader(std::make_shared<LightShader>())
    {
        m_rt.clear(ColorF(0.0, 1.0));
    }
    void LightView::clear()
    {
        m_rights.clear();
    }
    void LightView::push(const LightVM & light)
    {
        m_rights.push_back(light);
    }
    void LightView::draw(double time, const CameraView& camera) const
    {
        {
            ScopedRenderTarget2D target(m_rt);
            ScopedRenderStates2D state(BlendState::Additive);
            m_rt.clear(ColorF(0, 1));
            Transformer2D t2d(Mat3x2::Translate(-Constants::GameScreenOffset_v<float>), Transformer2D::Target::PushLocal);
            for (const auto& light : m_rights) {
                light.draw(time);
            }
        }
        {
            auto ps = m_shader->setSize(m_rt.size()).start();
            ScopedRenderStates2D state(BlendState::Multiplicative);
            m_rt.drawAt(camera.getCameraPos());
        }
    }
}
