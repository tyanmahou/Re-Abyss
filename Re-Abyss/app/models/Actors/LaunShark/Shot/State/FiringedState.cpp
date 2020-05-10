#include "FiringedState.hpp"
#include <abyss/params/Actors/LaunShark/ShotParam.hpp>

namespace abyss::LaunShark::Shot
{
    void FiringedState::start()
    {
        m_body->setAccel(m_rotate->getDir9() * ShotParam::Firinged::Accel);
        m_body->setMaxSpeed(m_rotate->getDir9() * ShotParam::Firinged::MaxSpeed);
    }
    void FiringedState::update(double dt)
    {
        m_body->update(dt);
    }

    void FiringedState::draw() const
    {
        m_pActor->getBindedView()->drawFiringed();
    }

}
