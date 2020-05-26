#include "AttackCtrlModel.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Player
{
    AttackCtrlModel::AttackCtrlModel(IActor* pActor):
        m_timer(0.5s, false, pActor->getUpdateTimer()),
        m_pActor(pActor)
    {}

    void AttackCtrlModel::startAttack()
    {
        m_timer.restart();
    }

    bool AttackCtrlModel::isAttacking() const
    {
        return !m_timer.reachedZero() && m_timer.isRunning();
    }

}
