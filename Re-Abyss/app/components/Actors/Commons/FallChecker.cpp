#include "FallChecker.hpp"
#include <abyss/modules/Actors/base/ActorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
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

        if (!m_pActor->getModule<Camera>()->isOutOfRoomDeath(m_body->getPos(), m_body->getHeight() / 2.0)) {
            return;
        }
        // 落下死
        m_isFall = true;

        if (m_deadChecker) {
            m_deadChecker->requestDead();
        }
    }
}
