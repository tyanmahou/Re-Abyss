#include "LaunSharkSwimState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/LaunShark/LaunSharkParam.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    void LaunSharkSwimState::onCollisionMap(ColDirection col)
    {
        LaunSharkBaseState::onCollisionMap(col);
        double time = LaunSharkParam::Swim::OnCollisionWaitTimeSec;
        if ((col.isLeft() || col.isRight()) && m_waitTimer.sF() <= time) {
            m_waitTimer.set(Duration(time));
        }
    }
    LaunSharkSwimState::LaunSharkSwimState():
        m_waitTimer(LaunSharkParam::Swim::WaitTimeSec, true, WorldTime::TimeMicroSec)
    {}
    void LaunSharkSwimState::start()
    {
        m_body
            ->setMaxSpeedX(LaunSharkParam::Swim::MaxSpeedX)
            .setSize(LaunSharkParam::Base::Size);
    }
    void LaunSharkSwimState::update(double dt)
    {
        double coefficient = Math::TwoPi / LaunSharkParam::Swim::MovePeriodSec;
        m_body->setVelocityY(LaunSharkParam::Swim::MoveRangeY * coefficient *
            s3d::Cos(m_timeCounter->getTotalTime() *  coefficient));

        this->LaunSharkBaseState::update(dt);

        if (m_waitTimer.reachedZero()) {
            s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_actor, *m_body);
            double f = m_body->isForward(Forward::Right) ? 1.0 : -1.0;
            if (f * d.x > 0) {
                auto distance = d.length();
                if (distance <= LaunSharkParam::Swim::AttackRange) {
                    this->changeState(LaunSharkActor::State::Attack);
                }else if (distance <= LaunSharkParam::Swim::LauncherRange) {
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
