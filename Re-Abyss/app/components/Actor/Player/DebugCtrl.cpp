#include "DebugCtrl.hpp"
#if ABYSS_DEBUG
#include <Siv3D.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/HP.hpp>
namespace abyss::Actor::Player
{
    DebugCtrl::DebugCtrl(ActorObj* pActor):
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