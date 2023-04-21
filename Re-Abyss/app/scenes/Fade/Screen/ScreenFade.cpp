#include <abyss/scenes/Fade/Screen/ScreenFade.hpp>

namespace abyss::Fade
{
    ScreenFade::ScreenFade() :
        m_view(std::make_unique<ScreenFadeView>())
    {
    }
    void ScreenFade::onFade(const s3d::RectF& rect, double t) const
    {
        m_view->draw(t, rect);
    }
}
