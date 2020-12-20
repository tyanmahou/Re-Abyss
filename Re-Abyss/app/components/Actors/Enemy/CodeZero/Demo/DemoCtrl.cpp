#include "DemoCtrl.hpp"

namespace abyss::Actor::Enemy::CodeZero::Demo
{
    DemoCtrl::DemoCtrl(IActor* pActor):
        m_pActor(pActor)
    {}
    bool DemoCtrl::moveToTarget(double dt)
    {
        if (m_pos.y <= m_targetPos.y) {
            m_pos = m_targetPos;
            return false;
        }
        m_pos.y += -120 * dt;
        return true;
    }
    void DemoCtrl::destroy() const
    {
        m_pActor->setActive(false);
        m_pActor->destroy();
    }
}
