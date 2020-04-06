#include "LaunSharkSwimState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/World/World.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    void LaunSharkSwimState::onCollisionMap(ColDirection col)
    {
        LaunSharkBaseState::onCollisionMap(col);
        double time = 0.5;
        if ((col.isLeft() || col.isRight()) && m_waitTimer.sF() <= 0.5) {
            m_waitTimer.set(0.5s);
        }
    }
    LaunSharkSwimState::LaunSharkSwimState():
        m_waitTimer(2.0, true, WorldTime::TimeMicroSec)
    {}
    void LaunSharkSwimState::start()
    {
        m_body
            ->setMaxSpeedX(180)
            .setSize({ 120, 60 });
    }
    void LaunSharkSwimState::update(double dt)
    {
        double coefficient = Math::TwoPi / 6.0;
        m_body->setVelocityY(20 * coefficient *
            s3d::Cos(m_timeCounter->getTotalTime() *  coefficient));

        this->LaunSharkBaseState::update(dt);

        if (m_waitTimer.reachedZero()) {
            s3d::Vec2 d = m_actor->getWorld()->getPlayerPos() - m_body->getPos();
            double f = m_body->isForward(Forward::Right) ? 1.0 : -1.0;
            if (f * d.x > 0) {
                auto distance = d.length();
                if (distance <= 200) {
                    this->changeState(LaunSharkActor::State::Attack);
                }else if (distance <= 500) {
                    this->changeState(LaunSharkActor::State::Launcher);
                } 
            }
        }
    }
    void LaunSharkSwimState::draw() const
    {
        m_actor->getBindedView()->drawSwim();
    }
}
