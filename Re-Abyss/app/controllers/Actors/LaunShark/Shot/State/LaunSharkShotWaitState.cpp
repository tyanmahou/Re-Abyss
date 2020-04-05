#include "LaunSharkShotWaitState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
namespace abyss
{
    LaunSharkShotWaitState::LaunSharkShotWaitState():
        m_timer(1s, true, WorldTime::TimeMicroSec)
    {}
    void LaunSharkShotWaitState::update(double dt)
    {
        m_body->setVelocity(m_rotate->getDir9() * 20);
        m_body->update(dt);
        if (m_timer.reachedZero()) {
            this->changeState(LaunSharkShotActor::State::Pursuit);
        }
    }
    void LaunSharkShotWaitState::draw() const
    {
        this->m_actor->getBindedView()->drawWait();
    }

}
