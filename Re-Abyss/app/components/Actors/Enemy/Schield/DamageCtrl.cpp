#include "DamageCtrl.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/base/IColliderModel.hpp>
#include <abyss/components/Actors/Enemy/Schield/FaceCtrl.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>

namespace abyss::Actor::Enemy::Schield
{
    DamageCtrl::DamageCtrl(IActor* pActor):
        Actor::DamageCtrl(pActor)
    {}

    void DamageCtrl::setup()
    {
        Actor::DamageCtrl::setup();

        m_face = m_pActor->find<FaceCtrl>();
    }
    void DamageCtrl::onCollisionStay(IActor* col)
    {
        if (!m_face->isOnFace()) {
            // 待機中以外はダメージを受けない
            return;
        }
        auto fromCol = col->find<IColliderModel>()->getCollider();
        auto faceCol = m_face->getCollider();
        if (!ColisionUtil::Intersects(fromCol, faceCol)) {
            return;
        }
        // face only
        Actor::DamageCtrl::onCollisionStay(col);
    }
}