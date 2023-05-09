#include <abyss/components/Fade/Screen/ScreenFade.hpp>

namespace abyss::Fade
{
    ScreenFade::ScreenFade() :
        m_view(std::make_unique<ScreenFadeView>())
    {
    }
    void ScreenFade::setColor(const s3d::ColorF& color)
    {
        m_view->setFadeColor(color);
    }
    void ScreenFade::onFade(const s3d::RectF& rect, double t) const
    {
        m_view->draw(t, rect);
    }
}
