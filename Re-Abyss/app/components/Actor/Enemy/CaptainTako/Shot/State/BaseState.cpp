#include "BaseState.hpp"

#include <abyss/components/Actor/Commons/AudioSource.hpp>

namespace abyss::Actor::Enemy::CaptainTako::Shot
{
    void BaseState::setup()
    {
        m_view = m_pActor->find<ViewCtrl<ShotVM>>().get();
    }

    Task<> BaseState::start()
    {
        this->m_pActor->find<AudioSource>()->playAt(U"Shot");
        co_return;
    }

    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}
