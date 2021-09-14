#include "BaseState.hpp"

#include <abyss/components/Actor/Common/AudioSource.hpp>

namespace abyss::Actor::Enemy::CaptainTako::Shot
{
    void BaseState::start()
    {
        this->m_pActor->find<AudioSource>()->playAt(U"Shot");
    }
}
