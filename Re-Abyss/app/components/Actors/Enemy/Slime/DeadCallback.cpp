#include "DeadCallback.hpp"
#include "SenserCtrl.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>

namespace abyss::Actor::Enemy::Slime
{
    void DeadCallback::onDead()
    {
        Enemy::DeadCallback::onDead();
        m_pActor->find<SenserCtrl>()->destroy();
    }
}