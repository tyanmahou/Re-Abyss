#include <abyss/components/Actor/Player/DebugCtrl.hpp>
#if ABYSS_DEBUG
#include <Siv3D.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/HP.hpp>

namespace abyss::Actor::Player
{
    DebugCtrl::DebugCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void DebugCtrl::onUpdate()
    {
        auto hp = m_pActor->find<HP>();
        if ((KeyShift + KeyD).down()) {
            hp->setHp(1);
        } else if (KeyD.down()) {
            hp->setHp(0);
        } else if (KeyS.down()) {
            hp->reset();
        }
    }

}
#endif
