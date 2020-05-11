#include "Phase2State.hpp"
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>

namespace abyss::CodeZero
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
            m_pActor->getLeftHand()->tryAttack();
        })
            .sleep(Param::Phase2::WaitAttack)
            .add([&]() {
            m_pActor->getRightHand()->tryAttack();
        })
            .sleep(Param::Phase2::WaitAttack)
            .add([&]() {
            m_pActor->getLeftHand()->tryAttack();
        })
            .sleep(Param::Phase2::WaitDualAttack)
            .add([&]() {
            m_pActor->getLeftHand()->tryAttack();
            m_pActor->getRightHand()->tryAttack();
        })
            .sleep(Param::Phase2::WaitRestart)
            .toStep(0)
            ;

        m_pActor->getLeftHand()->tryPursuit();
        m_pActor->getRightHand()->tryPursuit();
    }
    void Phase2State::update([[maybe_unused]]double dt)
    {
        if (m_hp->value() <= Param::Base::Hp * 1 / 3) {
            if (m_pActor->getLeftHand()->isPursuit() &&
                m_pActor->getRightHand()->isPursuit()) {
                this->changeState(State::Phase3);
            }
            return;
        }
        m_pattern->update();
    }
}
