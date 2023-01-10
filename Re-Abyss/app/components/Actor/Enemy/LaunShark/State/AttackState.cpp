#include <abyss/components/Actor/Enemy/LaunShark/State/AttackState.hpp>
#include <abyss/components/Actor/Enemy/LaunShark/State/SwimState.hpp>
#include <Siv3D.hpp>

#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/Param.hpp>
namespace abyss::Actor::Enemy::LaunShark
{
    AttackState::AttackState():
        m_attackTimer(Param::Attack::AttackTimeSec)
    {}

    void AttackState::start()
    {
        m_motion->set(Motion::Attack);

        m_body->setSize(Param::Attack::Size);
    }

    void AttackState::update()
    {
        double coefficient = Math::TwoPi / Param::Attack::MovePeriodSec;
        m_body->setVelocityY(Param::Attack::MoveRangeY * coefficient * s3d::Cos(m_timeCounter->getTotalTime() * coefficient));
        this->BaseState::update();

        m_attackTimer.update(m_pActor->deltaTime());
        if (m_attackTimer.isEnd()) {
            this->changeState<SwimState>();
        }
    }
}
