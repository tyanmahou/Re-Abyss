#include "SwimState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/LaunShark/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::LaunShark
{
    void SwimState::onCollisionMap(ColDirection col)
    {
        BaseState::onCollisionMap(col);
        double time = Param::Swim::OnCollisionWaitTimeSec;
        if ((col.isLeft() || col.isRight()) && m_waitTimer.sF() <= time) {
            m_waitTimer.set(Duration(time));
        }
    }
    SwimState::SwimState():
        m_waitTimer(Param::Swim::WaitTimeSec, true, WorldTime::TimeMicroSec)
    {}
    void SwimState::start()
    {
        m_body
            ->setMaxSpeedX(Param::Swim::MaxSpeedX)
            .setSize(Param::Base::Size);
    }
    void SwimState::update(double dt)
    {
        double coefficient = Math::TwoPi / Param::Swim::MovePeriodSec;
        m_body->setVelocityY(Param::Swim::MoveRangeY * coefficient *
            s3d::Cos(m_timeCounter->getTotalTime() *  coefficient));

        this->BaseState::update(dt);

        if (m_waitTimer.reachedZero()) {
            s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_actor, *m_body);
            double f = m_body->isForward(Forward::Right) ? 1.0 : -1.0;
            if (f * d.x > 0) {
                auto distance = d.length();
                if (distance <= Param::Swim::AttackRange) {
                    this->changeState(LaunSharkActor::State::Attack);
                }else if (distance <= Param::Swim::LauncherRange) {
                    this->changeState(LaunSharkActor::State::Launcher);
                } 
            }
        }
    }
    void SwimState::draw() const
    {
        m_actor->getBindedView()->drawSwim();
    }
}
