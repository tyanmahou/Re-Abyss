#include "DebugCtrl.hpp"
#if ABYSS_DEBUG
#include <Siv3D.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
namespace abyss::Actor::Player
{
    DebugCtrl::DebugCtrl(IActor* pActor):
        m_pActor(pActor)
    {}

    void DebugCtrl::setup()
    {}

    void DebugCtrl::onUpdate([[maybe_unused]]double dt)
    {
        auto hp = m_pActor->find<HPModel>();
        if (KeyD.down()) {
            hp->setHp(0);
        }
        if (KeyS.down()) {
            hp->reset();
        }
    }

}
#endif