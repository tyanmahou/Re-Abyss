#include "WaitState.hpp"
#include <abyss/views/Actors/CaptainTako/CpatainTakoVM.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/params/Actors/CaptainTako/Param.hpp>

namespace abyss::CaptainTako
{
    WaitState::WaitState() :
        m_waitTimer(Param::Wait::TimeSec, true, WorldTime::TimeMicroSec)
    {}
    void WaitState::update(double dt)
    {
        if (m_waitTimer.reachedZero() && m_actor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState(CaptainTakoActor::State::Charge);
        }
        BaseState::update(dt);
    }

    void WaitState::draw() const
    {
        m_actor->getBindedView()->drawWait();
    }
}
