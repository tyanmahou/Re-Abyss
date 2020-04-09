#include "LaunSharkShotFiringedState.hpp"
#include <abyss/params/Actors/LaunShark/LaunSharkShotParam.hpp>

namespace abyss
{
    void LaunSharkShotFiringedState::start()
    {
        m_body->setAccel(m_rotate->getDir9() * LaunSharkShotParam::Firinged::Accel);
        m_body->setMaxSpeed(m_rotate->getDir9() * LaunSharkShotParam::Firinged::MaxSpeed);
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
