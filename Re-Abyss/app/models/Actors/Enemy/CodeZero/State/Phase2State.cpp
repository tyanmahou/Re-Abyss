#include "Phase2State.hpp"
#include "Phase3State.hpp"
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>

namespace abyss::Actor::CodeZero
{
    Phase2State::Phase2State()
    {

    }
    void Phase2State::start()
    {
        m_pattern
            ->clear()
            .sleep(Param::Phase2::WaitInit)
            .add([&]() {
            m_parts->getLeftHand()->tryAttack();
        })
            .sleep(Param::Phase2::WaitAttack)
            .add([&]() {
            m_parts->getRightHand()->tryAttack();
        })
            .sleep(Param::Phase2::WaitAttack)
            .add([&]() {
            m_parts->getLeftHand()->tryAttack();
        })
            .sleep(Param::Phase2::WaitDualAttack)
            .add([&]() {
            m_parts->getLeftHand()->tryAttack();
            m_parts->getRightHand()->tryAttack();
        })
            .sleep(Param::Phase2::WaitRestart)
            .toStep(0)
            ;

        m_parts->getLeftHand()->tryPursuit();
        m_parts->getRightHand()->tryPursuit();
    }
    void Phase2State::update([[maybe_unused]]double dt)
    {
        if (m_hp->value() <= Param::Base::Hp * 1 / 3) {
            if (m_parts->getLeftHand()->isPursuit() &&
                m_parts->getRightHand()->isPursuit()) {
                this->changeState<Phase3State>();
            }
            return;
        }
        m_pattern->update();
    }
}
