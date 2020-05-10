#include "SwimState.hpp"

#include <abyss/views/Actors/Ikalien/IkalienVM.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/params/Actors/Ikalien/Param.hpp>
#include <Siv3D.hpp>
namespace abyss::Ikalien
{
    void SwimState::start()
    {
        m_body->setVelocity(m_rotate->getDir() * Param::Swim::Speed);
        m_body->setAccel(-m_rotate->getDir() * Param::Swim::Decel);
    }
    void SwimState::update(double dt)
    {
        if (m_body->getVelocity().length() <= 30) {
            this->changeState(State::Pursuit);
        }
        m_body->update(dt);
    }
    void SwimState::draw() const
    {
        m_pActor->getBindedView()->drawSwim();
    }

}
