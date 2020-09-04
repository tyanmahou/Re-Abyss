#include "DeadCallbackModel.hpp"
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/controllers/Effects/Effects.hpp>
#include <abyss/views/Actors/Common/EnemyDeadEffect.hpp>
#include <abyss/controllers/Camera/Camera.hpp>

namespace abyss::Actor::Enemy
{
    DeadCallbackModel::DeadCallbackModel(IActor* pActor):
        m_pActor(pActor)
    {}
    void DeadCallbackModel::onDead()
    {
        if (auto body = m_pActor->find<BodyModel>()) {
            m_pActor->getModule<Effects>()->addWorldFront<EnemyDeadEffect>(body->getPos());
        }
        if (m_useQuake) {
            m_pActor->getModule<Camera>()->startQuake(5.0, 0.3);
        }
    }
}

