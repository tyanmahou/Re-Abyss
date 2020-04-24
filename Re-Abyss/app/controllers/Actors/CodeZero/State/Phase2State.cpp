#include "Phase2State.hpp"
#include <abyss/params/Actors/CodeZero/Param.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/CodeZero/Hand/HandActor.hpp>

namespace abyss::CodeZero
{
    Phase2State::Phase2State()
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
            .sleep(Param::Attack::IntervalTimeSec)
            .add([&]() {
                m_actor->getLeftHand()->tryAttack();
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
    void Phase2State::start()
    {
        m_actor->getLeftHand()->tryPursuit();
        m_actor->getRightHand()->tryPursuit();
    }
    void Phase2State::update([[maybe_unused]]double dt)
    {
        if (m_hp->value() <= Param::Base::Hp * 1 / 3) {
            if (m_actor->getLeftHand()->isPursuit() &&
                m_actor->getRightHand()->isPursuit()) {
                this->changeState(State::Phase3);
            }
            return;
        }
        m_pattern.update();
    }
}
