#include "CaptainTakoWaitState.hpp"
#include <abyss/views/Actors/CaptainTako/CpatainTakoVM.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss
{
    CaptainTakoWaitState::CaptainTakoWaitState() :
        m_waitTimer(2.0, true, WorldTime::TimeMicroSec)
    {}
    void CaptainTakoWaitState::update(double dt)
    {
        if (m_waitTimer.reachedZero() && ActionSystem::Camera()->inScreen(m_body->getPos())) {
            this->changeState(CaptainTakoActor::State::Charge);
        }
        CaptainTakoBaseState::update(dt);
    }

    void CaptainTakoWaitState::draw() const
    {
        m_actor->getBindedView()->drawWait();
    }
}
