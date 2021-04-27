#include "DeadOnHItReceiver.hpp"
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/components/Actors/Commons/ReceiverData.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>

namespace abyss::Actor
{
    DeadOnHItReceiver::DeadOnHItReceiver(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void DeadOnHItReceiver::onStart()
    {
        m_deadChecker = m_pActor->find<DeadChecker>();
        m_cols = m_pActor->find<CollisionCtrl>();
        m_mapCol = m_pActor->find<MapCollider>();
    }
    void DeadOnHItReceiver::onPostCollision()
    {
        if (m_pActor->isDestroyed()) {
            return;
        }
        auto callback = [this]([[maybe_unused]] const ReceiverData& receiver) {
            // 当たって消える
            m_deadChecker->requestDead();
            return true;
        };

        if (m_cols && m_cols->anyThen<Tag::Receiver, ReceiverData>(callback)) {
            return;
        }
        if (m_mapCol && m_mapCol->anyThen<Tag::Receiver, ReceiverData>(callback)) {
            return;
        }
    }
}
