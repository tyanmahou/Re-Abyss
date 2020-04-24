#include "Phase3State.hpp"
#include <abyss/params/Actors/CodeZero/Param.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/CodeZero/Hand/HandActor.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/ActionSystem/ActManager.hpp>
#include <abyss/controllers/Actors/CodeZero/Shot/ShotActor.hpp>
namespace abyss::CodeZero
{
    Phase3State::Phase3State()
    {
        m_pattern
            .sleep(Param::Phase3::WaitRestart)
            .add([&]() {
                m_actor->getRightHand()->tryShotCharge();
                m_actor->getLeftHand()->tryShotCharge();
            })
            .sleep(Param::Phase3::WaitShot)
            .add([&]() {
                m_actor->getModule<World>()->create<Shot::ShotActor>(m_actor);
            })
            .sleep(Param::Phase3::WaitPursuit)
            .add([&]() {
                m_actor->getLeftHand()->tryPursuit();
                m_actor->getRightHand()->tryPursuit();
            })
            .sleep(Param::Phase3::WaitInitAttack)
            .add([&]() {
                m_actor->getRightHand()->tryAttack();
             })
            .sleep(Param::Phase3::WaitAttack)
            .add([&]() {
                 m_actor->getLeftHand()->tryAttack();
             })
            .sleep(Param::Phase3::WaitAttack)
            .add([&]() {
                 m_actor->getRightHand()->tryAttack();
             })
            .sleep(Param::Phase3::WaitRestart)
            .toStep(3, 1)
            .toStep(0)
        ;
    }
    void Phase3State::start()
    {
        m_actor->getRightHand()->tryShotCharge();
        m_actor->getLeftHand()->tryShotCharge();
    }
    void Phase3State::update([[maybe_unused]]double dt)
    {
        if (m_hp->isDead()) {
            m_actor->onDead();
            return;
        }
        m_pattern.update();
    }
}
