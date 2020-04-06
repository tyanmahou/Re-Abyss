#include "LaunSharkAttackState.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/views/Actors/LaunShark/LaunSharkVM.hpp>

namespace abyss
{
    LaunSharkAttackState::LaunSharkAttackState():
        m_attackTimer(LaunSharkParam::Attack().attackTimeSec, true, WorldTime::TimeMicroSec)
    {}

    void LaunSharkAttackState::start()
    {
        m_body->setSize(LaunSharkParam::Attack().size);
    }

    void LaunSharkAttackState::update(double dt)
    {
        const auto& param = LaunSharkParam::Attack();
        
        double coefficient = Math::TwoPi / param.movePeriodSec;
        m_body->setVelocityY(param.moveRangeY * coefficient *
            s3d::Cos(m_timeCounter->getTotalTime() * coefficient));

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
