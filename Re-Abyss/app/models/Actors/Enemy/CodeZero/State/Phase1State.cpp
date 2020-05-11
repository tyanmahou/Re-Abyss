#include "Phase1State.hpp"
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>

namespace abyss::CodeZero
{
    Phase1State::Phase1State()
    {
    }
    void Phase1State::start()
    {
        m_pattern
            ->clear()
            .sleep(Param::Phase1::WaitRestart)
            .add([&]() {
                m_pActor->getLeftHand()->tryAttack();
            })
            .sleep(Param::Phase1::WaitAttack)
            .add([&]() {
                m_pActor->getRightHand()->tryAttack();
            })
            .sleep(Param::Phase1::WaitRestart)
            .toStep(0)
        ;
    }
    void Phase1State::update([[maybe_unused]]double dt)
    {
        if (m_hp->value() <= Param::Base::Hp * 2 / 3) {
            if (m_pActor->getLeftHand()->isPursuit() &&
                m_pActor->getRightHand()->isPursuit()) {
                this->changeState(State::Phase2);
            }
            return;
        }
        m_pattern->update();
    }
}
