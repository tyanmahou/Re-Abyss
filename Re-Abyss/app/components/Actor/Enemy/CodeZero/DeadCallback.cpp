#include <abyss/components/Actor/Enemy/CodeZero/DeadCallback.hpp>


#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/State/DeadState.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    DeadCallback::DeadCallback(ActorObj* pActor) :
        m_pActor(pActor)
    {}

    void DeadCallback::onDead()
    {
        DeadState::Change(m_pActor);
    }
}
