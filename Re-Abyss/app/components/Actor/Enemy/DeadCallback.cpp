#include "DeadCallback.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Effects/Effects.hpp>
#include <abyss/modules/Camera/Camera.hpp>

#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/OutRoomChecker.hpp>

#include <abyss/views/Actor/Common/EnemyDeadEffect.hpp>


namespace abyss::Actor::Enemy
{
    DeadCallback::DeadCallback(ActorObj* pActor):
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
