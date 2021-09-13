#include "HandProxy.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/PursuitState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/AttackWaitState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/AttackState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/ShotChargeState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/RollingAttackState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    HandProxy::HandProxy(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void HandProxy::onStart()
    {
        m_state = m_pActor->find<StateCtrl>();
    }

    bool HandProxy::tryAttack()
    {
        if (m_state->isState<PursuitState>()) {
            m_state->changeState<AttackWaitState>();
            return true;
        }
        return false;
    }

    bool HandProxy::tryPursuit(const HandDesc& desc, bool slowStart)
    {
        if (m_state->isState<AttackState>() || m_state->isState<AttackWaitState>()) {
            return false;
        }
        m_state->changeState<PursuitState>(desc, slowStart);
        return true;
    }

    bool HandProxy::tryShotCharge()
    {
        if (!m_state->isState<PursuitState>()) {
            return false;
        }
        m_state->changeState<ShotChargeState>();
        return true;
    }

    bool HandProxy::tryRollingAttack()
    {
        m_state->changeState<RollingAttackState>();
        return true;
    }

    bool HandProxy::isShotCharge() const
    {
        return m_state->isState<ShotChargeState>();
    }

    bool HandProxy::isPursuit() const
    {
        return m_state->isState<PursuitState>();
    }

}
