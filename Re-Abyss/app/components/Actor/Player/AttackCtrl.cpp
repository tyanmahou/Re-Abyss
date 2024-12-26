#include <abyss/components/Actor/Player/AttackCtrl.hpp>
#include <Siv3D.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Player/Shot/Builder.hpp>

namespace abyss::Actor::Player
{
    AttackCtrl::AttackCtrl(ActorObj* pActor):
        m_pActor(pActor),
        m_timer(0.4)
    {
        m_timer.toEnd();
    }

    void AttackCtrl::reset()
    {
        m_timer.toEnd();
    }

    bool AttackCtrl::isAttacking() const
    {
        return !m_timer.isEnd();
    }

    void AttackCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_charge = m_pActor->find<ChargeCtrl>();
    }

    void AttackCtrl::onLastUpdate()
    {
        auto dt = m_pActor->deltaTime();
        m_timer.update(dt);
        if (!m_isActive || (m_timer.rate() <= 0.5)) {
            return;
        }

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
        m_timer.reset();

        double charge = m_charge->pop();
        m_pActor->getModule<Actors>()->create<Shot::Builder>(
            m_body->getCenterPos() + Vec2{ 30 * m_body->getForward().signH(), -1},
            m_body->getForward(), 
            charge
            );
    }

}
