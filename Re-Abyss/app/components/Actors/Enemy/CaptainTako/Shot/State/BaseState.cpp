#include "BaseState.hpp"

#include <abyss/controllers/System/System.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>

namespace abyss::Actor::Enemy::CaptainTako::Shot
{
    void BaseState::setup()
    {
        m_view = m_pActor->find<ViewModel<ShotVM>>().get();
    }

    void BaseState::start()
    {
        this->m_pActor->find<AudioSource>()->playAt(U"Shot");
    }

    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}
