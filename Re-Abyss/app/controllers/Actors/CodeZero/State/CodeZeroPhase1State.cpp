#include "CodeZeroPhase1State.hpp"
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/CodeZero/Hand/CodeZeroHandActor.hpp>

namespace abyss
{
    CodeZeroPhase1State::CodeZeroPhase1State():
        m_timer(3.0s, true, WorldTime::TimeMicroSec)
    {}
    void CodeZeroPhase1State::update([[maybe_unused]]double dt)
    {
        if (!m_timer.reachedZero()) {
            return;
        }
        if (m_hp->value() <= CodeZeroParam::Base::Hp * 2 / 3) {
            this->changeState(State::Phase2);
            return;
        }
        switch (m_step) {
        case 0:
            m_actor->getRightHand()->tryAttack();
            m_timer.restart(s3d::Duration(CodeZeroParam::Attack::IntervalTimeSec));
            break;
        case 1:
            m_actor->getLeftHand()->tryAttack();
            m_timer.restart(s3d::Duration(CodeZeroParam::Attack::IntervalTimeSec));
            break;
        case 2:
            m_actor->getRightHand()->tryAttack();
            m_timer.restart(2s);
            break;
        case 3:
            m_actor->getLeftHand()->tryAttack();
            m_actor->getRightHand()->tryAttack();
            m_timer.restart(4s);
            break;
        default:
            break;
        }
        ++m_step;
        m_step %= 4;
        
    }
}
