#include "CodeZeroPhase3State.hpp"
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/CodeZero/Hand/CodeZeroHandActor.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/ActionSystem/ActManager.hpp>
#include <abyss/views/Actors/CodeZero/Shot/CodeZeroShotChargeEffect.hpp>

namespace abyss
{
    CodeZeroPhase3State::CodeZeroPhase3State()
    {
        m_pattern
            .sleep(3s)
            .add([&]() {
                m_actor->getRightHand()->tryShotCharge();
                m_actor->getLeftHand()->tryShotCharge();
            })
            .sleep(1s)
            .add([&]() {
                m_actor->getModule<World>()->addEffect<CodeZeroShotChargeEffect>(m_actor->getPos());
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
            .sleep(CodeZeroParam::Attack::IntervalTimeSec)
            .add([&]() {
                 m_actor->getLeftHand()->tryAttack();
             })
            .sleep(CodeZeroParam::Attack::IntervalTimeSec)
            .add([&]() {
                 m_actor->getRightHand()->tryAttack();
             })
        ;
    }
    void CodeZeroPhase3State::start()
    {
        m_actor->getRightHand()->tryShotCharge();
        m_actor->getLeftHand()->tryShotCharge();
    }
    void CodeZeroPhase3State::update([[maybe_unused]]double dt)
    {
        if (m_hp->isDead()) {
            m_actor->onDead();
            return;
        }
        m_pattern.update();
    }
}
