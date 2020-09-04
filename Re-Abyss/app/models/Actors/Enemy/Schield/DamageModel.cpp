#include "DamageModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/base/IColliderModel.hpp>
#include <abyss/models/Actors/Enemy/Schield/FaceCtrlModel.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>

namespace abyss::Actor::Enemy::Schield
{
    DamageModel::DamageModel(IActor* pActor):
        abyss::DamageModel(pActor)
    {}

    void DamageModel::setup()
    {
        abyss::DamageModel::setup();

        m_face = m_pActor->find<FaceCtrlModel>();
    }
    void DamageModel::onCollisionStay(IActor* col)
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
        abyss::DamageModel::onCollisionStay(col);

    }
}