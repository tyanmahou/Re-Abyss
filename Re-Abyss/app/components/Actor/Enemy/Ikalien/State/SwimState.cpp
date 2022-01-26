#include <abyss/components/Actor/Enemy/Ikalien/State/SwimState.hpp>
#include <abyss/components/Actor/Enemy/Ikalien/State/PursuitState.hpp>

#include <abyss/params/Actor/Enemy/Ikalien/Param.hpp>
#include <Siv3D.hpp>
namespace abyss::Actor::Enemy::Ikalien
{
    void SwimState::start()
    {
        m_body->setVelocity(m_rotate->getDir() * Param::Swim::Speed);
        m_body->setAccel(-m_rotate->getDir() * Param::Swim::Decel);
        m_motion->set(Motion::Swim);
    }
    void SwimState::update()
    {
        if (m_body->getVelocity().length() <= 30) {
            this->changeState<PursuitState>();
        }
    }
}
