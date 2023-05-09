#include <abyss/components/Fade/IrisOut/IrisOutFade.hpp>
#include <abyss/commons/Constants.hpp>

namespace abyss::Fade
{
    IrisOutFade::IrisOutFade() :
        IrisOutFade(Constants::AppResolutionF / 2.0)
    {}
    IrisOutFade::IrisOutFade(const s3d::Vec2& pos) :
        m_pos(pos),
        m_view(std::make_unique<IrisOutFadeView>())
    {
    }
    void IrisOutFade::setColor(const s3d::ColorF& color)
    {
        m_view->setFadeColor(color);
    }

    void IrisOutFade::onFade(const s3d::RectF& rect, double t) const
    {
        m_view->draw(t, m_pos, rect);
    }
}
