#include "AttackState.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/views/Actors/LaunShark/LaunSharkVM.hpp>
#include <abyss/params/Actors/LaunShark/Param.hpp>
namespace abyss::LaunShark
{
    AttackState::AttackState():
        m_attackTimer(Param::Attack::AttackTimeSec, true, WorldTime::TimeMicroSec)
    {}

    void AttackState::start()
    {
        m_body->setSize(Param::Attack::Size);
    }

    void AttackState::update(double dt)
    {
        double coefficient = Math::TwoPi / Param::Attack::MovePeriodSec;
        m_body->setVelocityY(Param::Attack::MoveRangeY * coefficient * s3d::Cos(m_timeCounter->getTotalTime() * coefficient));

        this->BaseState::update(dt);

        if (m_attackTimer.reachedZero()) {
            this->changeState(LaunSharkActor::State::Swim);
        }
    }

    void AttackState::draw() const
    {
        m_actor->getBindedView()->drawAttack();
    }

}
