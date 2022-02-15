#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor
{
    BehaviorCtrl::BehaviorCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}
    
    void BehaviorCtrl::setSequence(std::function<Coro::Task<>(ActorObj*)> sequence)
    {
        m_sequence.reset(std::bind(sequence, m_pActor));
    }
    void BehaviorCtrl::setBehavior(std::function<Coro::Task<>(ActorObj*)> behavior)
    {
        m_task.reset(std::bind(behavior, m_pActor));
    }
    void BehaviorCtrl::onUpdate()
    {
        if (!m_isActive) {
            return;
        }
        m_sequence.moveNext();
        m_task.moveNext();
    }
}
