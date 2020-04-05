#include "LaunSharkShotFiringedState.hpp"

namespace abyss
{
    void LaunSharkShotFiringedState::start()
    {
        m_body->setAccel(m_rotate->getDir9() * 120);
        m_body->setMaxSpeed(m_rotate->getDir9() * 360.0);
    }
    void LaunSharkShotFiringedState::update(double dt)
    {
        m_body->update(dt);
    }

    void LaunSharkShotFiringedState::draw() const
    {
        m_actor->getBindedView()->drawFiringed();
    }

}
