#include "LightView.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>

namespace abyss
{
    void LightView::clear()
    {
        m_rights.clear();
    }
    void LightView::push(const LightVM & light)
    {
        m_rights.push_back(light);
    }
    void LightView::draw(const s3d::Vec2& pos) const
    {
        m_rt.clear(ColorF(0.0, 1.0));
        {
            ScopedRenderTarget2D target(m_rt);
            Transformer2D t2d(Mat3x2::Translate(-Constants::GameScreenOffset_v<float>), Transformer2D::Target::PushLocal);

            for (const auto& light : m_rights) {
                light.draw();
            }
        }
        ScopedRenderStates2D state(BlendState::Multiplicative);
        m_rt.drawAt(pos);
    }
}
