#include "PursuitState.hpp"
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    void PursuitState::start()
    {
        if (m_kind->isLeftHand()) {
            if (m_parent->isPhase1() || m_parent->isPhase3()) {
                *m_hand = HandModel::CreateLeftPhase1();
            } else {
                *m_hand =HandModel::CreateLeftPhase2();
            }
        } else {
            if (m_parent->isPhase1() || m_parent->isPhase3()) {
                *m_hand = HandModel::CreateRightPhase1();
            } else {
                *m_hand = HandModel::CreateRightPhase2();
            }
        }

        m_hand->startForPursuit(*m_body);
    }

    void PursuitState::update(double dt)
    {
        m_hand->updateRotate(*m_rotate, dt);

        auto playerPos = m_pActor->getModule<Player::PlayerActor>()->getPos();
        m_hand->updateForPursuit(
            playerPos,
            m_parent->getPos(),
            *m_body,
            dt
        );
    }

    void PursuitState::lastUpdate()
    {
    }
}
