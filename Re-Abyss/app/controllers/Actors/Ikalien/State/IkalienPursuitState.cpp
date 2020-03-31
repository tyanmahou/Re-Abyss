#include "IkalienPursuitState.hpp"

#include <abyss/views/Actors/Ikalien/IkalienVM.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
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
        constexpr double speed = s3d::Math::ToRadians(60);
        double rotate = m_ikalien->getRotate();
        if (m_ikalien->getDir().cross(d) > 0) {
            rotate +=  speed * dt;
        } else {
            rotate -= speed * dt;
        }
        m_ikalien->setRotate(rotate);

        constexpr s3d::Vec2 pivotOffset{ 0, -15 };
        Vec2 nextPivot = Mat3x2::Rotate(rotate).transform(pivotOffset);
        m_body->setPivot(nextPivot);

        m_body->setVelocity(m_ikalien->getDir() * 30);
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
