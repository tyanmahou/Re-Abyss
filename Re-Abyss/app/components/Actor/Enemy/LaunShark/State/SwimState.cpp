#include <abyss/components/Actor/Enemy/LaunShark/State/SwimState.hpp>
#include <abyss/components/Actor/Enemy/LaunShark/State/AttackState.hpp>
#include <abyss/components/Actor/Enemy/LaunShark/State/LauncherState.hpp>

#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/components/Actor/Common/MapCollider.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    SwimState::SwimState():
        m_waitTimer(Param::Swim::WaitTimeSec)
    {}
    void SwimState::start()
    {
        m_motion->set(Motion::Swim);
        m_body
            ->setMaxSpeedX(Param::Swim::MaxSpeedX)
            .setSize(Param::Base::Size);
    }
    void SwimState::update()
    {
        m_waitTimer.update(m_pActor->deltaTime());
        double coefficient = Math::TwoPi / Param::Swim::MovePeriodSec;
        m_body->setVelocityY(Param::Swim::MoveRangeY * coefficient *
            s3d::Cos(m_timeCounter->getTotalTime() *  coefficient));
        this->BaseState::update();

        if (m_waitTimer.isEnd()) {
            s3d::Vec2 d = ActorUtils::ToPlayer(*m_pActor, *m_body);
            double f = m_body->isForward(Forward::Right()) ? 1.0 : -1.0;
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
        if (m_mapCol->isHitWall() && m_waitTimer.rest() <= time) {
            m_waitTimer.reset(time);
        }
    }
}
