#include "BehaviorCtrl.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>

namespace abyss::Actor
{
    BehaviorCtrl::BehaviorCtrl(IActor* pActor):
        m_pActor(pActor)
    {}
    void BehaviorCtrl::setBehavior(std::function<Coro::Task<>(IActor*)> behavior)
    {
        m_task = std::make_unique<Coro::Task<>>(behavior(m_pActor));
    }
    void BehaviorCtrl::onUpdate()
    {
        if (!m_isActive) {
            return;
        }
        if (m_task) {
            m_task->moveNext();
        }
    }
}
