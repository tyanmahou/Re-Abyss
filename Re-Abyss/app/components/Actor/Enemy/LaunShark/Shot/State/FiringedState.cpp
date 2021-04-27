#include "FiringedState.hpp"
#include <abyss/params/Actor/Enemy/LaunShark/ShotParam.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    Task<> FiringedState::start()
    {
        m_body->setAccel(m_rotate->getDir9() * ShotParam::Firinged::Accel);
        m_body->setMaxSpeed(m_rotate->getDir9() * ShotParam::Firinged::MaxSpeed);
        co_return;
    }

    void FiringedState::draw() const
    {
        (*m_view)->drawFiringed();
    }
}
