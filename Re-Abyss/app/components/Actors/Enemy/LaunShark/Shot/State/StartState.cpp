#include "StartState.hpp"
#include "WaitState.hpp"
#include <abyss/params/Actors/Enemy/LaunShark/ShotParam.hpp>
namespace abyss::Actor::Enemy::LaunShark::Shot
{
    Task<> StartState::start()
    {
        m_body->setVelocity(m_rotate->getDir9() * ShotParam::Start::Speed);
        m_body->setAccel(-m_rotate->getDir9() * ShotParam::Start::Decel);
        co_return;
    }

    void StartState::update()
    {
        if (m_body->getVelocity().length() <= 30) {
            this->changeState<WaitState>();
        }
    }

    void StartState::draw() const
    {
        (*m_view)->drawWait();
    }
}
