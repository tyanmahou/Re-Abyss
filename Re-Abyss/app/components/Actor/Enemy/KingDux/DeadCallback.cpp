#include <abyss/components/Actor/Enemy/KingDux/DeadCallback.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/DeadState.hpp>
namespace abyss::Actor::Enemy::KingDux
{
    DeadCallback::DeadCallback(ActorObj* pActor) :
        m_pActor(pActor)
    {}
    void DeadCallback::onDead()
    {
        DeadState::Change(m_pActor);
    }
}