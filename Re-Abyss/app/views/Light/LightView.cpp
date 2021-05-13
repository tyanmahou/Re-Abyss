#include "LightView.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
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
        m_lights.clear();
        m_rights.clear();
    }
    void LightView::push(const LightVM & light)
    {
        m_rights.push_back(light);
    }
    void LightView::render(double time) const
    {
        ScopedRenderTarget2D target(m_rt);
        ScopedRenderStates2D state(BlendState::Additive);
        m_rt.clear(ColorF(0, 1));
        for (const auto& light : m_rights) {
            light.draw(time);
        }
        for (const auto& light : m_lights) {
            light(time);
        }
    }
    s3d::ScopedCustomShader2D LightView::start(const s3d::ColorF & color) const
    {
        return m_shader
            ->setBgColor(color)
            .setLightsTexture(m_rt)
            .start();
    }
}
