#include "SwimState.hpp"
#include "PursuitState.hpp"
#include <abyss/params/Actors/Enemy/Ikalien/Param.hpp>
#include <Siv3D.hpp>
namespace abyss::Ikalien
{
    void SwimState::start()
    {
        m_body->setVelocity(m_rotate->getDir() * Param::Swim::Speed);
        m_body->setAccel(-m_rotate->getDir() * Param::Swim::Decel);

        m_draw->request(DrawModel::Kind::Swim);
    }
    void SwimState::update([[maybe_unused]]double dt)
    {
        if (m_body->getVelocity().length() <= 30) {
            this->changeState<PursuitState>();
        }
    }
}
