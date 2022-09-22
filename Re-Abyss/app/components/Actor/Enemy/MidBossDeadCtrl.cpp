#include <abyss/components/Actor/Enemy/MidBossDeadCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include "MidBossDeadCtrl.hpp"

namespace abyss::Actor::Enemy
{
    MidBossDeadCtrl::MidBossDeadCtrl(ActorObj* pActor, s3d::uint32 id) :
        m_pActor(pActor),
        m_id(id)
    {
    }

    void MidBossDeadCtrl::onStart()
    {
        // 撃破済みなら破棄
        if (m_pActor->getModule<Temporary>()->onFlag(key())) {
            m_pActor->destroy();
            return;
        }
    }

    void MidBossDeadCtrl::onDead()
    {
        m_pActor->getModule<Temporary>()->saveFlagRestart(key());
    }
    TempKey MidBossDeadCtrl::key() const
    {
        return TempKey::MidBossKill(m_pActor->getModule<Stage>()->mapName(), m_id);
    }
}
