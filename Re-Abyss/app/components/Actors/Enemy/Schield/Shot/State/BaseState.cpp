#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Schield::Shot
{
    void BaseState::setup()
    {
        m_view = m_pActor->find<ViewCtrl<ShotVM>>().get();
    }

    Task<> BaseState::start()
    {
        co_return;
    }

    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}
