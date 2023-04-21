#include <abyss/scenes/Fade/IrisOut/IrisOutFade.hpp>

namespace abyss::Fade
{
    IrisOutFade::IrisOutFade() :
        m_pos(0, 0),
        m_view(std::make_unique<IrisOutFadeView>())
    {}

    void IrisOutFade::onFade(const s3d::RectF& rect, double t) const
    {
        m_view->draw(t, m_pos, rect);
    }
}
