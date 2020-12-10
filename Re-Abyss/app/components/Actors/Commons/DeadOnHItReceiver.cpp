#include "DeadOnHItReceiver.hpp"
#include <abyss/controllers/Actors/ActInclude.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/components/Actors/Commons/ReceiverData.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>
namespace abyss::Actor
{
    DeadOnHItReceiver::DeadOnHItReceiver(IActor* pActor):
        m_pActor(pActor)
    {}
    void DeadOnHItReceiver::onStart()
    {
        m_deadChecker = m_pActor->find<DeadChecker>();
    }
    void DeadOnHItReceiver::onCollisionStay(ICollider * col)
    {
        if (m_pActor->isDestroyed()) {
            return;
        }
        col->isThen<Tag::Receiver, ReceiverData>([this]([[maybe_unused]]const ReceiverData& receiver) {
            // 当たって消える
            m_deadChecker->requestDead();
        });
    }
}
