#include <abyss/views/Fade/ScreenFadeView.hpp>

namespace abyss::Fade
{
    void ScreenFadeView::draw(double t, const s3d::RectF& rect) const
    {
        if (!fadeTimeAdjust(t)) {
            rect.draw(m_fadeColor);
            return;
        }
        rect.draw(ColorF(m_fadeColor, t));
    }
}
