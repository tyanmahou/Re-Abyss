#include "FallChecker.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
\
namespace abyss::Actor
{
    FallChecker::FallChecker(IActor* pActor):
        m_pActor(pActor)
    {}

    void FallChecker::setup()
    {
        m_deadChecker = m_pActor->find<DeadChecker>();
        m_body = m_pActor->find<BodyModel>();
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
