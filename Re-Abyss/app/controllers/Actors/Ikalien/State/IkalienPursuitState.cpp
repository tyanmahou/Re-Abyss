#include "IkalienPursuitState.hpp"

#include <abyss/views/Actors/Ikalien/IkalienVM.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/params/Actors/Ikalien/IkalienParam.hpp>
#include <Siv3D.hpp>
namespace abyss
{
    IkalienPursuitState::IkalienPursuitState():
        m_timer(2s, true, WorldTime::TimeMicroSec)
    {}
    void IkalienPursuitState::start()
    {
        m_body->noneResistanced();
    }
    void IkalienPursuitState::update(double dt)
    {
        s3d::Vec2 d = m_actor->getWorld()->getPlayerPos() - m_body->getPos();
        const double speed = s3d::Math::ToRadians(IkalienParam::Pursuit::RotateDeg);
        double rotate = m_rotate->getRotate();
        if (m_rotate->getDir().cross(d) > 0) {
            rotate +=  speed * dt;
        } else {
            rotate -= speed * dt;
        }
        m_rotate->setRotate(rotate);

        Vec2 nextPivot = Mat3x2::Rotate(rotate).transform(IkalienParam::Base::Pivot);
        m_body->setPivot(nextPivot);

        m_body->setVelocity(m_rotate->getDir() * IkalienParam::Pursuit::Speed);
        m_body->update(dt);
        if (m_timer.reachedZero()) {
            this->changeState(IkalienActor::State::Swim);
        }
    }
    void IkalienPursuitState::draw() const
    {
        m_actor->getBindedView()->drawPursuit();
    }

}
