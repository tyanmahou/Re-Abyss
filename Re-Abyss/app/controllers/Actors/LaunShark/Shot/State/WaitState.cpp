#include "WaitState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>

#include <abyss/params/Actors/LaunShark/ShotParam.hpp>

namespace abyss::LaunShark::Shot
{
    WaitState::WaitState():
        m_timer(ShotParam::Wait::Time, true, WorldTime::TimeMicroSec)
    {}
    void WaitState::update(double dt)
    {
        m_body->setVelocity(m_rotate->getDir9() * ShotParam::Wait::Speed);
        m_body->update(dt);
        if (m_timer.reachedZero()) {
            this->changeState(State::Pursuit);
        }
    }
    void WaitState::draw() const
    {
        this->m_actor->getBindedView()->drawWait();
    }

}
