#include "DeadCallbackModel.hpp"
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/Common/EnemyDeadEffect.hpp>

namespace abyss::Enemy
{
    DeadCallbackModel::DeadCallbackModel(IActor* pActor):
        m_pActor(pActor)
    {}
    void DeadCallbackModel::onDead()
    {
        if (auto body = m_pActor->find<BodyModel>()) {
            m_pActor->getModule<World>()->addEffect<EnemyDeadEffect>(body->getPos());
        }
    }
}

