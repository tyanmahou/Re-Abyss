#include "SimpleDrawCallbackView.hpp"
#include <abyss/views/Actors/Ooparts/base/OopartsView.hpp>
#include <abyss/views/Actors/Common/KiraKiraEffect.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Ooparts
{
    SimpleDrawCallbackView::SimpleDrawCallbackView(OopartsView* view):
        m_effect([view] {return Time::FromSec(view->getTime()); }),
        m_effectTimer(0.05, true, [view] {return Time::FromSec(view->getTime()); })
    {}

    void SimpleDrawCallbackView::onDraw(const s3d::Vec2& pos) const
    {
        if (m_effectTimer.update()) {
            if (RandomBool(0.7)) {
                m_effect.add<KiraKiraEffect>(pos + RandomVec2({ -15, 15 }, { 0, 20 }));
            } else {
                m_effect.add<KiraKiraEffect>(pos + RandomVec2(17), KiraKiraEffect::Type2);
            }
        }
        m_effect.update();
    }
}
