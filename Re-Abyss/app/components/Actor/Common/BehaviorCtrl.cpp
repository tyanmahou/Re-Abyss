#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/StateCtrl.hpp>

namespace abyss::Actor
{
    BehaviorCtrl::BehaviorCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void BehaviorCtrl::setup(Executer executer)
    {
        executer.on<IPostUpdate>().addBefore<StateCtrl>();
    }
    
    void BehaviorCtrl::setSequence(std::function<Coro::Task<>(ActorObj*)> sequence)
    {
        m_sequence.reset(std::bind(sequence, m_pActor));
    }
    void BehaviorCtrl::setBehavior(std::function<Coro::Task<>(ActorObj*)> behavior)
    {
        m_behavior.reset(std::bind(behavior, m_pActor));
    }
    void BehaviorCtrl::onPostUpdate()
    {
        if (m_isActiveSeq) {
            m_sequence.moveNext();
        }

        if (m_isActiveBehavior) {
            m_behavior.moveNext();
        }
    }

    void BehaviorCtrl::onStateStart()
    {
        m_isActiveSeq = true;
        m_isActiveBehavior = false;
    }
}
