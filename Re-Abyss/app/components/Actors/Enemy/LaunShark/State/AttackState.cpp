#include "AttackState.hpp"
#include "SwimState.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/Param.hpp>
namespace abyss::Actor::Enemy::LaunShark
{
    AttackState::AttackState()
    {}

    Task<> AttackState::start()
    {
        m_attackTimer = ActorUtils::CreateTimer(*m_pActor, Param::Attack::AttackTimeSec);
        m_body->setSize(Param::Attack::Size);
        co_return;
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

    void AttackState::draw() const
    {
        (*m_view)->drawAttack();
    }
}
