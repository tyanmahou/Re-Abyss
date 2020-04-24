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
            .sleep(3s)
            .add([&]() {
                m_actor->getRightHand()->tryShotCharge();
                m_actor->getLeftHand()->tryShotCharge();
            })
            .sleep(1s)
            .add([&]() {
                m_actor->getModule<World>()->create<Shot::ShotActor>(m_actor);
            })
            .sleep(3s)
            .add([&]() {
                m_actor->getLeftHand()->tryPursuit();
                m_actor->getRightHand()->tryPursuit();
            })
            .sleep(2s)
            .add([&]() {
                m_actor->getRightHand()->tryAttack();
             })
            .sleep(Param::Attack::IntervalTimeSec)
            .add([&]() {
                 m_actor->getLeftHand()->tryAttack();
             })
            .sleep(Param::Attack::IntervalTimeSec)
            .add([&]() {
                 m_actor->getRightHand()->tryAttack();
             })
            .sleep(3s)
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
