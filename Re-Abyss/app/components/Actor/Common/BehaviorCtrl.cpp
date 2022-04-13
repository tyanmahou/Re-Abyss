#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/utils/Coro/Task/Wait.hpp>

namespace abyss::Actor
{
    BehaviorCtrl::BehaviorCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void BehaviorCtrl::setSequence(std::function<Coro::Task<>(BehaviorCtrl*)> sequence)
    {
        m_sequence.reset(std::bind(sequence, this));
    }
    void BehaviorCtrl::setBehavior(std::function<Coro::Task<>(ActorObj*)> behavior)
    {
        m_behavior.reset(std::bind(behavior, m_pActor));
    }

    Coro::Task<> BehaviorCtrl::setBehaviorAndWait(std::function<Coro::Task<>(ActorObj*)> behavior)
    {
        this->setBehavior(behavior);
        co_await Coro::WaitUntil([this] {
            return this->isDoneBehavior();
        });
    }

    bool BehaviorCtrl::isDoneBehavior() const
    {
        return m_behavior.isDone();
    }
    void BehaviorCtrl::setup(Executer executer)
    {
        executer.on<IPostUpdate>().addBefore<StateCtrl>();
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
