#include "AttackCtrlModel.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Player
{
    AttackCtrlModel::AttackCtrlModel(IActor* pActor):
        m_timer(0.4s, false, pActor->getUpdateTimer()),
        m_pActor(pActor)
    {}

    void AttackCtrlModel::reset()
    {
        m_timer.restart();
        m_timer.pause();
    }

    void AttackCtrlModel::startAttack()
    {
        m_timer.restart();
    }

    bool AttackCtrlModel::isAttacking() const
    {
        return !m_timer.reachedZero() && m_timer.isRunning();
    }

}
