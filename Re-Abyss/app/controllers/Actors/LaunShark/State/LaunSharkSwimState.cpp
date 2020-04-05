#include "LaunSharkSwimState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/LaunShark/LaunSharkVM.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    void LaunSharkSwimState::onCollisionMap(ColDirection col)
    {
        LaunSharkBaseState::onCollisionMap(col);
        if (col.isLeft() || col.isRight()) {
            m_waitTimer.set(0.5s);
        }
    }
    LaunSharkSwimState::LaunSharkSwimState():
        m_waitTimer(1.5s, true, WorldTime::TimeMicroSec)
    {}
    void LaunSharkSwimState::start()
    {
        m_body
            ->setMaxSpeedX(180)
            .setSize({ 120, 40 });
    }
    void LaunSharkSwimState::update(double dt)
    {
        m_body->setVelocityY(20 * s3d::Cos(m_timeCounter->getTotalTime()));

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
