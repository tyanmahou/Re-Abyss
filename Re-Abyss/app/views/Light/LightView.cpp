#include "LightView.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/debugs/Menu/Menu.hpp>
#include <abyss/views/Light/LightShader.hpp>

namespace abyss
{
    LightView::LightView():
        m_rt(Constants::GameScreenSize_v<int32>.asPoint()),
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
    void LightView::draw(const s3d::Texture& dest, double time, const s3d::ColorF& color) const
    {
        {
            ScopedRenderTarget2D target(m_rt);
            ScopedRenderStates2D state(BlendState::Additive);
            m_rt.clear(ColorF(0, 1));
            for (const auto& light : m_rights) {
                light.draw(time);
            }
        }
        {
            Transformer2D t2d(Mat3x2::Identity(), Transformer2D::Target::SetLocal);

#if ABYSS_DEBUG
            if (Debug::Menu::IsDebug(U"disable-darkness")) {
                dest.draw();
                return;
            }
#endif
            auto ps = m_shader
                ->setBgColor(color)
                .setLightsTexture(m_rt)
                .start();
            dest.draw();
        }
    }
}
