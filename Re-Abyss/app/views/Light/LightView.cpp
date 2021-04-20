#include "LightView.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/views/Camera/CameraView.hpp>

namespace abyss
{
    LightView::LightView():
        m_rt(Constants::GameScreenSize_v<uint32>.x, Constants::GameScreenSize_v<uint32>.y)
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
            m_rt.clear(ColorF(0, 1));
            Transformer2D t2d(Mat3x2::Translate(-Constants::GameScreenOffset_v<float>), Transformer2D::Target::PushLocal);
            for (const auto& light : m_rights) {
                light.draw(time);
            }
        }
        ScopedRenderStates2D state(BlendState::Multiplicative);
        m_rt.drawAt(camera.getCameraPos());
    }
}
