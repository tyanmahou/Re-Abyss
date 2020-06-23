#include "WaitState.hpp"
#include <abyss/views/Actors/Enemy/Schield/SchieldVM.hpp>
#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/controllers/System/System.hpp>
#include <abyss/models/Actors/Commons/ActorTimeModel.hpp>

namespace abyss::Schield
{
    WaitState::WaitState()
    {}
    void WaitState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, Param::Wait::TimeSec);
        m_pActor->find<ActorTimeModel>()->resetDrawTime();
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
