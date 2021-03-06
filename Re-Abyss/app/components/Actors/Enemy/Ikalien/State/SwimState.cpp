#include "SwimState.hpp"
#include "PursuitState.hpp"
#include <abyss/params/Actors/Enemy/Ikalien/Param.hpp>
#include <Siv3D.hpp>
namespace abyss::Actor::Enemy::Ikalien
{
    Task<> SwimState::start()
    {
        m_body->setVelocity(m_rotate->getDir() * Param::Swim::Speed);
        m_body->setAccel(-m_rotate->getDir() * Param::Swim::Decel);
        co_return;
    }
    void SwimState::update()
    {
        if (m_body->getVelocity().length() <= 30) {
            this->changeState<PursuitState>();
        }
    }

    void SwimState::draw() const
    {
        (*m_view)->drawSwim();
    }
}
