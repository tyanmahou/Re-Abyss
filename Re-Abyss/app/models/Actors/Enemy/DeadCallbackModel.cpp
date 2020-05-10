#include "DeadCallbackModel.hpp"
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/Common/EnemyDeadEffect.hpp>

namespace abyss::Enemy
{
    DeadCallbackModel::DeadCallbackModel(EnemyActor* pActor):
        m_pActor(pActor)
    {}
    void DeadCallbackModel::onDead()
    {
        m_pActor->destroy();
        m_pActor->getModule<World>()->addEffect<EnemyDeadEffect>(m_pActor->getPos());
    }
}

