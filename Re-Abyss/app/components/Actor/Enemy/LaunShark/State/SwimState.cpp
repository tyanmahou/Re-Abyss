#include "SwimState.hpp"
#include "AttackState.hpp"
#include "LauncherState.hpp"
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/components/Actor/Commons/MapCollider.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    SwimState::SwimState()
    {}
    Task<> SwimState::start()
    {
        m_waitTimer = ActorUtils::CreateTimer(*m_pActor, Param::Swim::WaitTimeSec);
        m_body
            ->setMaxSpeedX(Param::Swim::MaxSpeedX)
            .setSize(Param::Base::Size);
        co_return;
    }
    void SwimState::update()
    {
        double coefficient = Math::TwoPi / Param::Swim::MovePeriodSec;
        m_body->setVelocityY(Param::Swim::MoveRangeY * coefficient *
            s3d::Cos(m_timeCounter->getTotalTime() *  coefficient));

        this->BaseState::update();

        if (m_waitTimer.reachedZero()) {
            s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
            double f = m_body->isForward(Forward::Right) ? 1.0 : -1.0;
            if (f * d.x > 0) {
                auto distance = d.length();
                if (distance <= Param::Swim::AttackRange) {
                    this->changeState<AttackState>();
                }else if (distance <= Param::Swim::LauncherRange) {
                    this->changeState<LauncherState>();
                } 
            }
        }
    }
    void SwimState::lastUpdate()
    {
        BaseState::lastUpdate();
        double time = Param::Swim::OnCollisionWaitTimeSec;
        if (m_mapCol->isHitWall() && m_waitTimer.sF() <= time) {
            m_waitTimer.set(Duration(time));
        }
    }

    void SwimState::draw() const
    {
        (*m_view)->drawSwim();
    }
}
