#include "Phase3State.hpp"
#include <abyss/params/Actors/CodeZero/Param.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/ActionSystem/ActManager.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Shot/ShotActor.hpp>
namespace abyss::CodeZero
{
    Phase3State::Phase3State()
    {

    }
    void Phase3State::start()
    {
        m_pattern
            ->clear()
            .sleep(Param::Phase3::WaitRestart)
            .add([&]() {
            m_pActor->getRightHand()->tryShotCharge();
            m_pActor->getLeftHand()->tryShotCharge();
        })
            .sleep(Param::Phase3::WaitShot)
            .add([&]() {
            m_pActor->getModule<World>()->create<Shot::ShotActor>(m_pActor);
        })
            .sleep(Param::Phase3::WaitPursuit)
            .add([&]() {
            m_pActor->getLeftHand()->tryPursuit();
            m_pActor->getRightHand()->tryPursuit();
        })
            .sleep(Param::Phase3::WaitInitAttack)
            .add([&]() {
            m_pActor->getRightHand()->tryAttack();
        })
            .sleep(Param::Phase3::WaitAttack)
            .add([&]() {
            m_pActor->getLeftHand()->tryAttack();
        })
            .sleep(Param::Phase3::WaitAttack)
            .add([&]() {
            m_pActor->getRightHand()->tryAttack();
        })
            .sleep(Param::Phase3::WaitRestart)
            .toStep(3, 1)
            .toStep(0)
            ;
        m_pActor->getRightHand()->tryShotCharge();
        m_pActor->getLeftHand()->tryShotCharge();
    }
    void Phase3State::update([[maybe_unused]]double dt)
    {
        if (m_hp->isDead()) {
            return;
        }
        m_pattern->update();
    }
}
