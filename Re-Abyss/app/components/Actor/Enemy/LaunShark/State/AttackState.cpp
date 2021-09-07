#include "AttackState.hpp"
#include "SwimState.hpp"
#include <Siv3D.hpp>

#include <abyss/modules/World/World.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/Param.hpp>
namespace abyss::Actor::Enemy::LaunShark
{
    AttackState::AttackState()
    {}

    void AttackState::start()
    {
        m_motion->set(Motion::Attack);

        m_attackTimer = ActorUtils::CreateTimer(*m_pActor, Param::Attack::AttackTimeSec);
        m_body->setSize(Param::Attack::Size);
    }

    void AttackState::update()
    {
        double coefficient = Math::TwoPi / Param::Attack::MovePeriodSec;
        m_body->setVelocityY(Param::Attack::MoveRangeY * coefficient * s3d::Cos(m_timeCounter->getTotalTime() * coefficient));

        this->BaseState::update();

        if (m_attackTimer.reachedZero()) {
            this->changeState<SwimState>();
        }
    }
}
