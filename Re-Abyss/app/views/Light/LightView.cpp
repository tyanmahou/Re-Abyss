#include <abyss/views/Light/LightView.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/views/Shader/Light/LightShader.hpp>
#include <abyss/views/Light/LightUtil.hpp>

namespace
{
    struct ScopedLight
    {
    public:
        ScopedLight(const Optional<RenderTexture>& rt):
            target(rt),
            state(BlendState::Additive)
        {}
    private:
        ScopedRenderTarget2D target;
        ScopedRenderStates2D state;
    };
    struct ScopedShadow
    {
    public:
        ScopedShadow(const Optional<RenderTexture>& rt) :
            target(rt),
            state(BlendState::Default2D),
            colurMul(Palette::Black)
        {}
    private:
        ScopedRenderTarget2D target;
        ScopedRenderStates2D state;
        ScopedColorMul2D colurMul;
    };
}
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
        m_rt.clear(ColorF(0, 1));
    }
    void LightView::add(std::function<void(double)> lightDraw)
    {
        ScopedLight light(m_rt);
        lightDraw(m_time);
    }
    void LightView::addCircle(const s3d::Vec2& pos, double radius, double brightness)
    {
        ScopedLight light(m_rt);
        LightUtil::DrawCircleLight(pos, radius, brightness, m_time);
    }
    void LightView::addPie(const s3d::Vec2& pos, double radius, double startAngle, double angle, double brightness)
    {
        ScopedLight light(m_rt);
        LightUtil::DrawPieLight(pos, radius, startAngle, angle, brightness, m_time);
    }
    void LightView::addArc(const s3d::Vec2& pos, double radius, double innerAntiRadius, double startAngle, double angle, double brightness)
    {
        ScopedLight light(m_rt);
        LightUtil::DrawArcLight(pos, radius, innerAntiRadius, startAngle, angle, brightness, m_time);
    }
    void LightView::addShadow(std::function<void(double)> shadowDraw)
    {
        ScopedShadow shadow(m_rt);
        shadowDraw(m_time);
    }
    s3d::ScopedCustomShader2D LightView::start(const s3d::ColorF & color) const
    {
        return m_shader
            ->setBgColor(color)
            .setLightsTexture(m_rt)
            .start();
    }
}
