#include "ActDrawCallbackView.hpp"
#include <Siv3D.hpp>
#include <abyss/views/Actors/Ooparts/base/OopartsVM.hpp>
#include <abyss/views/Actors/Common/KiraKiraEffect.hpp>
#include <abyss/controllers/System/System.hpp>

namespace abyss::Actor::Ooparts
{
    ActDrawCallbackView::ActDrawCallbackView(OopartsVM* view, Manager* manager):
        m_pManager(manager),
        m_effectTimer(0.05, true, [view] {return Time::FromSec(view->getTime()); })
    {}
    void ActDrawCallbackView::onDraw(const s3d::Vec2& pos) const
    {
        auto* effects = m_pManager->getModule<Effects>();
        if (m_effectTimer.update()) {
            if (RandomBool(0.7)) {
                effects->addWorldBack<KiraKiraEffect>(pos + RandomVec2({ -15, 15 }, { 0, 20 }));
            } else {
                effects->addWorldBack<KiraKiraEffect>(pos + RandomVec2(17), KiraKiraEffect::Type2);
            }
        }
    }
}
