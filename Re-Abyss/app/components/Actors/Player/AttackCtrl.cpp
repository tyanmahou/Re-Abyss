#include "AttackCtrl.hpp"
#include <Siv3D.hpp>

#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Player/Shot/Builder.hpp>

namespace abyss::Actor::Player
{
    AttackCtrl::AttackCtrl(IActor* pActor):
        m_timer(0.4s, false, pActor->getUpdateClock()),
        m_pActor(pActor)
    {}

    void AttackCtrl::reset()
    {
        m_timer.restart();
        m_timer.pause();
    }

    bool AttackCtrl::isAttacking() const
    {
        return !m_timer.reachedZero() && m_timer.isRunning();
    }

    void AttackCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_charge = m_pActor->find<ChargeCtrl>();
    }

    void AttackCtrl::onLastUpdate()
    {
        if (!m_isActive || (m_timer.progress0_1() <= 0.5 && m_timer.isRunning())) {
            return;
        }
        auto dt = m_pActor->deltaTime();

        // 攻撃
        if (m_charge->update(dt)) {
            startAttack();
        }
    }

    void AttackCtrl::onStateStart()
    {
        m_isActive = false;
    }

    void AttackCtrl::startAttack()
    {
        m_timer.restart();

        double charge = m_charge->pop();
        m_pActor->getModule<World>()->create<Shot::Builder>(
            m_body->getPos() + Vec2{ 30 * m_body->getForward(), -1 }, 
            m_body->getForward(), 
            charge
            );
    }

}
