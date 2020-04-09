#include "LaunSharkAttackState.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/views/Actors/LaunShark/LaunSharkVM.hpp>
#include <abyss/params/Actors/LaunShark/LaunSharkParam.hpp>
namespace abyss
{
    LaunSharkAttackState::LaunSharkAttackState():
        m_attackTimer(LaunSharkParam::Attack::AttackTimeSec, true, WorldTime::TimeMicroSec)
    {}

    void LaunSharkAttackState::start()
    {
        m_body->setSize(LaunSharkParam::Attack::Size);
    }

    void LaunSharkAttackState::update(double dt)
    {
        double coefficient = Math::TwoPi / LaunSharkParam::Attack::MovePeriodSec;
        m_body->setVelocityY(LaunSharkParam::Attack::MoveRangeY * coefficient * s3d::Cos(m_timeCounter->getTotalTime() * coefficient));

        this->LaunSharkBaseState::update(dt);

        if (m_attackTimer.reachedZero()) {
            this->changeState(LaunSharkActor::State::Swim);
        }
    }

    void LaunSharkAttackState::draw() const
    {
        m_actor->getBindedView()->drawAttack();
    }

}
