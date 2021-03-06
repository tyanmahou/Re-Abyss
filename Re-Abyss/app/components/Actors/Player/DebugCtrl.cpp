#include "DebugCtrl.hpp"
#if ABYSS_DEBUG
#include <Siv3D.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
namespace abyss::Actor::Player
{
    DebugCtrl::DebugCtrl(IActor* pActor):
        m_pActor(pActor)
    {}

    void DebugCtrl::onUpdate()
    {
        auto hp = m_pActor->find<HP>();
        if (KeyD.down()) {
            hp->setHp(0);
        }
        if (KeyS.down()) {
            hp->reset();
        }
    }

}
#endif