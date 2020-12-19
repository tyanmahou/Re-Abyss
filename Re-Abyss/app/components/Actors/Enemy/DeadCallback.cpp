#include "DeadCallback.hpp"
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/controllers/Effects/Effects.hpp>
#include <abyss/views/Actors/Common/EnemyDeadEffect.hpp>
#include <abyss/controllers/Camera/Camera.hpp>

#include <abyss/components/Actors/Commons/OutRoomChecker.hpp>

namespace abyss::Actor::Enemy
{
    DeadCallback::DeadCallback(IActor* pActor):
        m_pActor(pActor)
    {}
    void DeadCallback::onDead()
    {
        if (auto outRoom = m_pActor->find<OutRoomChecker>()) {
            // エリア外で死んだ場合は何もしない
            if (outRoom->isOutRoom()) {
                return;
            }
        }
        if (auto body = m_pActor->find<Body>()) {
            m_pActor->getModule<Effects>()->addWorldFront<EnemyDeadEffect>(body->getPos());
        }
        if (m_useQuake) {
            m_pActor->getModule<Camera>()->startQuake(5.0, 0.3);
        }
    }
}

