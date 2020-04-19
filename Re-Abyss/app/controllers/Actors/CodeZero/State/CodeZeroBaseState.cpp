#include "CodeZeroBaseState.hpp"
#include <abyss/views/Actors/CodeZero/Body/CodeZeroBodyVM.hpp>

#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/CodeZero/Hand/CodeZeroHandActor.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    CodeZeroBaseState::CodeZeroBaseState():
        m_attackIntervalTimer(CodeZeroParam::Attack::IntervalTimeSec, true, WorldTime::TimeMicroSec)
    {}
    void CodeZeroBaseState::setup()
    {}
    void CodeZeroBaseState::update([[maybe_unused]]double dt)
    {
        if (m_attackIntervalTimer.reachedZero()) {
            switch (Random(0, 2)) {
            case 0:
                m_actor->getLeftHand()->tryAttack();
                break;
            case 1:
                m_actor->getRightHand()->tryAttack();
                break;
            case 2:
                m_actor->getLeftHand()->tryAttack();
                m_actor->getRightHand()->tryAttack();
                break;
            }
            m_attackIntervalTimer.restart();
        }
    }
    void CodeZeroBaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }
}
