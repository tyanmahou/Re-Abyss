#include "AttackCtrl.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Actor::Player
{
    AttackCtrl::AttackCtrl(IActor* pActor):
        m_timer(0.4s, false, pActor->getUpdateTimer()),
        m_pActor(pActor)
    {}

    void AttackCtrl::reset()
    {
        m_timer.restart();
        m_timer.pause();
    }

    void AttackCtrl::startAttack()
    {
        m_timer.restart();
    }

    bool AttackCtrl::isAttacking() const
    {
        return !m_timer.reachedZero() && m_timer.isRunning();
    }

}
