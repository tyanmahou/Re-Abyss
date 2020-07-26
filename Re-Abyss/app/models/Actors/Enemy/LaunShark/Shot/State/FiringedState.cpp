#include "FiringedState.hpp"
#include <abyss/params/Actors/Enemy/LaunShark/ShotParam.hpp>

namespace abyss::LaunShark::Shot
{
    void FiringedState::start()
    {
        m_body->setAccel(m_rotate->getDir9() * ShotParam::Firinged::Accel);
        m_body->setMaxSpeed(m_rotate->getDir9() * ShotParam::Firinged::MaxSpeed);
    }

    void FiringedState::draw() const
    {
        (*m_view)->drawFiringed();
    }
}
