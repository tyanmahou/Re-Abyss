#include "SwimState.hpp"
#include "PursuitState.hpp"
#include <abyss/params/Actor/Enemy/Ikalien/Param.hpp>
#include <Siv3D.hpp>
namespace abyss::Actor::Enemy::Ikalien
{
    void SwimState::start()
    {
        m_body->setVelocity(m_rotate->getDir() * Param::Swim::Speed);
        m_body->setAccel(-m_rotate->getDir() * Param::Swim::Decel);
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
