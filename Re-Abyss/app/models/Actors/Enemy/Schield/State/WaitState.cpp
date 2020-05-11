#include "WaitState.hpp"
#include <abyss/views/Actors/Enemy/Schield/SchieldVM.hpp>
#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>

namespace abyss::Schield
{
    WaitState::WaitState()
    {}
    void WaitState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, Param::Wait::TimeSec);
    }
    void WaitState::update(double dt)
    {
        BaseState::update(dt);

        if (m_timer.reachedZero() && m_pActor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState(State::AttackPlus);
        }
    }

    void WaitState::draw() const
    {
        m_pActor->getBindedView()->drawWait();
    }
}
