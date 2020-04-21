#include "CodeZeroHandPursuitState.hpp"
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>

namespace abyss
{
    void CodeZeroHandPursuitState::update(double dt)
    {
        m_hand->updateRotate(*m_rotate, dt);

        auto playerPos = m_actor->getModule<PlayerActor>()->getPos();
        m_hand->updateForPursuit(
            playerPos,
            m_parent->getPos(),
            *m_body,
            dt
        );
    }
    void CodeZeroHandPursuitState::start()
    {
        if (m_actor->isLeftHand()) {
            if (m_parent->isPhase1() || m_parent->isPhase3()) {
                *m_hand = CodeZeroHandModel::CreateLeftPhase1();
            } else {
                *m_hand = CodeZeroHandModel::CreateLeftPhase2();
            }
        } else {
            if (m_parent->isPhase1() || m_parent->isPhase3()) {
                *m_hand = CodeZeroHandModel::CreateRightPhase1();
            } else {
                *m_hand = CodeZeroHandModel::CreateRightPhase2();
            }
        }

        m_hand->startForPursuit(*m_body);
    }
}
