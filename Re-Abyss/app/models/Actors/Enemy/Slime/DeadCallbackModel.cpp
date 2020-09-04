#include "DeadCallbackModel.hpp"
#include "SenserCtrlModel.hpp"
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>

namespace abyss::Actor::Enemy::Slime
{
    void DeadCallbackModel::onDead()
    {
        Enemy::DeadCallbackModel::onDead();
        m_pActor->find<SenserCtrlModel>()->destroy();
    }
}