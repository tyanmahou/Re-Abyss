#include "AttackState.hpp"
#include "SwimState.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/Param.hpp>
namespace abyss::LaunShark
{
    AttackState::AttackState()
    {}

    void AttackState::start()
    {
        m_attackTimer = ActorUtils::CreateTimer(*m_pActor, Param::Attack::AttackTimeSec);
        m_body->setSize(Param::Attack::Size);

        m_draw->request(DrawModel::Kind::Attack);
    }

    void AttackState::update(double dt)
    {
        double coefficient = Math::TwoPi / Param::Attack::MovePeriodSec;
        m_body->setVelocityY(Param::Attack::MoveRangeY * coefficient * s3d::Cos(m_timeCounter->getTotalTime() * coefficient));

        this->BaseState::update(dt);

        if (m_attackTimer.reachedZero()) {
            this->changeState<SwimState>();
        }
    }
}
