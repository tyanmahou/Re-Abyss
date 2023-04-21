#include <abyss/views/Fade/IrisOutFadeView.hpp>
#include <abyss/commons/Constants.hpp>

namespace abyss::Fade
{
    IrisOutFadeView::IrisOutFadeView() :
        m_maskShader(Constants::AppResolution)
    {
    }
    void IrisOutFadeView::draw(double t, const s3d::Vec2& pos, const s3d::RectF& rect) const
    {
        if (!fadeTimeAdjust( t)) {
            rect.draw(m_fadeColor);
            return;
        }
        static auto easing = [](double t) {
            return ((t - 0.3f) * (t - 0.3f) * (t - 0.3f) + 0.027) / 0.37f;
        };
        auto mask = m_maskShader.notEqual([&] {
            auto alpha = EaseInOut(Easing::Linear, 1.0 - t);
            Circle(pos, rect.w * easing(1.0 - t)).draw(ColorF(0, alpha));
            });
        rect.draw(m_fadeColor);
    }
}
