#include "FallChecker.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/components/Actor/Common/DeadCheacker.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
\
namespace abyss::Actor
{
    FallChecker::FallChecker(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void FallChecker::onStart()
    {
        m_deadChecker = m_pActor->find<DeadChecker>();
        m_body = m_pActor->find<Body>();
    }

    void FallChecker::onLastUpdate()
    {
        if (m_isFall) {
            return;
        }

        if (!m_pActor->getModule<RoomManager>()->isOutOfRoomDeath(m_body->getPos(), m_body->getHeight() / 2.0)) {
            return;
        }
        // 落下死
        m_isFall = true;

        if (m_deadChecker) {
            m_deadChecker->requestDead();
        }
    }
}
