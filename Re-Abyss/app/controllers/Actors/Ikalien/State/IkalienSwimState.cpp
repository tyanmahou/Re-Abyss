#include "IkalienSwimState.hpp"

#include <abyss/views/Actors/Ikalien/IkalienVM.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/params/Actors/Ikalien/IkalienParam.hpp>
#include <Siv3D.hpp>
namespace abyss
{
    void IkalienSwimState::start()
    {
        m_body->setVelocity(m_rotate->getDir() * IkalienParam::Swim::Speed);
        m_body->setAccel(-m_rotate->getDir() * IkalienParam::Swim::Deccel);
    }
    void IkalienSwimState::update(double dt)
    {
        if (m_body->getVelocity().length() <= 30) {
            this->changeState(IkalienActor::State::Pursuit);
        }
        m_body->update(dt);
    }
    void IkalienSwimState::draw() const
    {
        m_actor->getBindedView()->drawSwim();
    }

}
