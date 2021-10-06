#include "LightView.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/views/Light/LightShader.hpp>
#include <abyss/views/Light/LightUtil.hpp>

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
    }
    void LightView::addCircle(const s3d::Vec2& pos, double radius, double brightness)
    {
        m_lights.push_back([=](double time){
            LightUtil::DrawCircleLight(pos, radius, brightness, time);
        });
    }
    void LightView::addPie(const s3d::Vec2& pos, double radius, double startAngle, double angle, double brightness)
    {
        m_lights.push_back([=](double time) {
            LightUtil::DrawPieLight(pos, radius, startAngle, angle, brightness, time);
        });
    }
    void LightView::addArc(const s3d::Vec2& pos, double radius, double innerAntiRadius, double startAngle, double angle, double brightness)
    {
        m_lights.push_back([=](double time) {
            LightUtil::DrawArcLight(pos, radius, innerAntiRadius, startAngle, angle, brightness, time);
        });
    }
    void LightView::addShadow(std::function<void(double)> shadowDraw)
    {
        m_lights.push_back([d = std::move(shadowDraw)](double time) {
            ScopedRenderStates2D state(BlendState::Multiplicative);
            d(time);
        });
    }
    void LightView::render(double time) const
    {
        ScopedRenderTarget2D target(m_rt);
        ScopedRenderStates2D state(BlendState::Additive);
        m_rt.clear(ColorF(0, 1));
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
