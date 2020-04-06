#include "LaunSharkAttackState.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/views/Actors/LaunShark/LaunSharkVM.hpp>

namespace abyss
{
    LaunSharkAttackState::LaunSharkAttackState():
        m_attackTimer(4.0, true, WorldTime::TimeMicroSec)
    {}

    void LaunSharkAttackState::start()
    {
        m_body->setSize({120, 60});
    }

    void LaunSharkAttackState::update(double dt)
    {
        double coefficient = Math::TwoPi / 3.0;
        m_body->setVelocityY(40 * coefficient *
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
