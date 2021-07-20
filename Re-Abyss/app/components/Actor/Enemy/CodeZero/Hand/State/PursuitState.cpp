#include "PursuitState.hpp"
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    void PursuitState::start()
    {
        if (m_kind->isLeftHand()) {
            if (m_parent->isPhase1() || m_parent->isPhase3()) {
                *m_hand = HandCtrl::CreateLeftPhase1();
            } else {
                *m_hand =HandCtrl::CreateLeftPhase2();
            }
        } else {
            if (m_parent->isPhase1() || m_parent->isPhase3()) {
                *m_hand = HandCtrl::CreateRightPhase1();
            } else {
                *m_hand = HandCtrl::CreateRightPhase2();
            }
        }

        m_hand->startForPursuit(*m_body);
    }

    void PursuitState::update()
    {
        auto dt = m_pActor->deltaTime();
        m_hand->updateRotate(*m_rotate, dt);

        const auto& playerPos = ActorUtils::PlayerPos(*m_pActor);
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
