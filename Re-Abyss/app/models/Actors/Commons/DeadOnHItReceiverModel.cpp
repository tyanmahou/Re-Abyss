#include "DeadOnHItReceiverModel.hpp"
#include <abyss/controllers/Actors/ActInclude.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>

namespace abyss
{
    DeadOnHItReceiverModel::DeadOnHItReceiverModel(IActor* pActor):
        m_pActor(pActor)
    {}
    void DeadOnHItReceiverModel::setup()
    {
        m_deadChecker = m_pActor->find<Actor::DeadChecker>();
    }
    void DeadOnHItReceiverModel::onCollisionStay(IActor * col)
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
