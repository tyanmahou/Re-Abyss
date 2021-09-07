#include "StartState.hpp"
#include "WaitState.hpp"
#include <abyss/params/Actor/Enemy/LaunShark/ShotParam.hpp>
namespace abyss::Actor::Enemy::LaunShark::Shot
{
    void StartState::start()
    {
        m_motion->set(Motion::Wait);
        m_body->setVelocity(m_rotate->getDir9() * ShotParam::Start::Speed);
        m_body->setAccel(-m_rotate->getDir9() * ShotParam::Start::Decel);
    }

    void StartState::update()
    {
        if (m_body->getVelocity().length() <= 30) {
            this->changeState<WaitState>();
        }
    }
}
