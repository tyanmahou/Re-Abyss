#include "DeadOnHItReceiver.hpp"
#include <abyss/components/Actor/Common/MapCollider.hpp>
#include <abyss/components/Actor/Common/DeadCheacker.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Receiver.hpp>
#include <abyss/modules/Physics/base/Tag.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor
{
    DeadOnHItReceiver::DeadOnHItReceiver(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void DeadOnHItReceiver::onStart()
    {
        m_deadChecker = m_pActor->find<DeadChecker>();
        m_cols = m_pActor->find<ColCtrl>();
        m_mapCol = m_pActor->find<MapCollider>();
    }
    void DeadOnHItReceiver::onPostCollision()
    {
        if (m_pActor->isDestroyed()) {
            return;
        }
        if (m_cols && m_cols->isHitBy<Col::Receiver>()) {
            // 当たって消える
            m_deadChecker->requestDead();
            return;
        }
        if (m_mapCol && m_mapCol->isHitBy<Physics::Tag::Receiver>()) {
            m_deadChecker->requestDead();
            return;
        }
    }
}
