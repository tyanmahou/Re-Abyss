#include "PursuitState.hpp"
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    void PursuitState::start()
    {
        if (m_kind->isLeftHand()) {
            if (m_parent->isPhase1() || m_parent->isPhase3()) {
                m_handMove->setParam(HandRecipe::CreateLeftPhase1());
            } else {
                m_handMove->setParam(HandRecipe::CreateLeftPhase2());
            }
        } else {
            if (m_parent->isPhase1() || m_parent->isPhase3()) {
                m_handMove->setParam(HandRecipe::CreateRightPhase1());
            } else {
                m_handMove->setParam(HandRecipe::CreateRightPhase2());
            }
        }

        m_handMove->startForPursuit();
    }

    void PursuitState::update()
    {
        m_handMove->updateRotate();
        m_handMove->updateForPursuit();
    }

    void PursuitState::lastUpdate()
    {
    }
}
