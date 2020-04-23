#include "CodeZeroPhase1State.hpp"
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/CodeZero/Hand/CodeZeroHandActor.hpp>

namespace abyss
{
    CodeZeroPhase1State::CodeZeroPhase1State()
    {
        m_pattern
            .sleep(3s)
            .add([&]() {
                m_actor->getRightHand()->tryAttack();
            })
            .sleep(CodeZeroParam::Attack::IntervalTimeSec)
            .add([&]() {
                m_actor->getLeftHand()->tryAttack();
            })
            .sleep(CodeZeroParam::Attack::IntervalTimeSec)
            .add([&]() {
                m_actor->getRightHand()->tryAttack();
            })
            .sleep(2s)
            .add([&]() {
                m_actor->getLeftHand()->tryAttack();
                m_actor->getRightHand()->tryAttack();
            })
            .sleep(4s)
            .toStep(0)
        ;
    }
    void CodeZeroPhase1State::update([[maybe_unused]]double dt)
    {
        if (m_hp->value() <= CodeZeroParam::Base::Hp * 2 / 3) {
            if (m_actor->getLeftHand()->isPursuit() &&
                m_actor->getRightHand()->isPursuit()) {
                this->changeState(State::Phase2);
            }
            return;
        }
        m_pattern.update();
    }
}
