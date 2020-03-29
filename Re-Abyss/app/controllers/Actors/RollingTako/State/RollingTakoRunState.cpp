#include "RollingTakoRunState.hpp"
#include <abyss/views/Actors/RollingTako/RollingTakoVM.hpp>

namespace abyss
{
    void RollingTakoRunState::update(double dt)
    {
        if (m_body->isForward(Forward::Left)) {
            m_body->setAccelX(-180.0);
        } else if (m_body->isForward(Forward::Right)) {
            m_body->setAccelX(180.0f);
        }
        RollingTakoBaseState::update(dt);
    }

    void RollingTakoRunState::draw() const
    {
        m_actor->getBindedView()->drawRun();
    }
}
