#include "Phase1State.hpp"
#include <abyss/params/Actors/CodeZero/Param.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/CodeZero/Hand/HandActor.hpp>

namespace abyss::CodeZero
{
    Phase1State::Phase1State()
    {
        m_pattern
            .sleep(3s)
            .add([&]() {
                m_actor->getLeftHand()->tryAttack();
            })
            .sleep(Param::Attack::IntervalTimeSec)
            .add([&]() {
                m_actor->getRightHand()->tryAttack();
            })
            .sleep(3s)
            .toStep(0)
        ;
    }
    void Phase1State::update([[maybe_unused]]double dt)
    {
        if (m_hp->value() <= Param::Base::Hp * 2 / 3) {
            if (m_actor->getLeftHand()->isPursuit() &&
                m_actor->getRightHand()->isPursuit()) {
                this->changeState(State::Phase2);
            }
            return;
        }
        m_pattern.update();
    }
}
