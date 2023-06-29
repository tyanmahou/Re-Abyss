#include <abyss/components/Actor/Enemy/CaptainTako/Shot/State/BaseState.hpp>

#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Enemy/CaptainTako/SeDef.hpp>

namespace abyss::Actor::Enemy::CaptainTako::Shot
{
    void BaseState::start()
    {
        this->m_pActor->find<AudioSource>()->playAt(SeDef::Shot);
    }
}
