#include "DamageModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/base/IColliderModel.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>

namespace abyss::Schield
{
    DamageModel::DamageModel(IActor* pActor):
        abyss::DamageModel(pActor)
    {}

    void DamageModel::setup()
    {
        abyss::DamageModel::setup();

        m_state = m_pActor->find<StateModel<SchieldActor>>();
    }
    void DamageModel::onCollisionStay(IActor* col)
    {
        if (m_state->getState() != SchieldActor::State::Wait) {
            // 待機中以外はダメージを受けない
            return;
        }
        auto fromCol = col->find<IColliderModel>()->getCollider();
        auto faceCol = m_state->getActor()->getFaceCollider();
        if (!ColisionUtil::Intersects(fromCol, faceCol)) {
            return;
        }
        // face only
        abyss::DamageModel::onCollisionStay(col);

    }
}