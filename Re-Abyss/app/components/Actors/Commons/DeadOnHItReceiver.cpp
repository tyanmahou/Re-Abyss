#include "DeadOnHItReceiver.hpp"
#include <abyss/controllers/Actors/ActInclude.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>

namespace abyss::Actor
{
    DeadOnHItReceiver::DeadOnHItReceiver(IActor* pActor):
        m_pActor(pActor)
    {}
    void DeadOnHItReceiver::onStart()
    {
        m_deadChecker = m_pActor->find<DeadChecker>();
    }
    void DeadOnHItReceiver::onCollisionStay(IActor * col)
    {
        if (m_pActor->isDestroyed()) {
            return;
        }
        col->accept([this](const Receiver&) {
            // 当たって消える
            m_deadChecker->requestDead();
        });
    }
}
