#include "HandProxy.h"
#include <abyss/controllers/Actors/base/IActor.hpp>

#include <abyss/components/Actors/Enemy/CodeZero/Hand/State/PursuitState.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/State/AttakWaitState.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/State/AttackState.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/State/ShotChargeState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    HandProxy::HandProxy(IActor* pActor):
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

    bool HandProxy::tryPursuit()
    {
        if (m_state->isState<AttackState>() || m_state->isState<AttackWaitState>()) {
            return false;
        }
        m_state->changeState<PursuitState>();
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

    bool HandProxy::isShotCharge() const
    {
        return m_state->isState<ShotChargeState>();
    }

    bool HandProxy::isPursuit() const
    {
        return m_state->isState<PursuitState>();
    }

}
