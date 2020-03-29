#include "RollingTakoWaitState.hpp"

#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/RollingTako/RollingTakoVM.hpp>

namespace abyss
{
    void RollingTakoWaitState::update(double dt)
    {
        s3d::Vec2 d = m_actor->getWorld()->getPlayerPos() - m_body->getPos();
        double f = m_body->isForward(Forward::Right) ? 1.0 : -1.0;
        if (f * d.x > 0 && d.length() <= 300) {
            this->changeState(RollingTakoActor::Run);
        }
        RollingTakoBaseState::update(dt);
    }

    void RollingTakoWaitState::draw() const
    {
        m_actor->getBindedView()->drawWait();
    }
}
