#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>

namespace abyss::Actor
{
    BehaviorCtrl::BehaviorCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void BehaviorCtrl::setSequence(const BehaviorSeqFunc& sequence)
    {
        m_sequence.reset([seq = std::bind(sequence, m_pActor), this]()->Coro::Fiber<> {
            co_await seq().each([this](const BehaviorFunc& behavior) {
                this->setBehavior(behavior);
                this->setActiveBehavior(true);
            });
        });
    }
    void BehaviorCtrl::setBehavior(const BehaviorFunc& behavior)
    {
        m_behavior.reset(std::bind(behavior, m_pActor));
    }

    bool BehaviorCtrl::isDoneBehavior() const
    {
        return m_behavior.isDone();
    }
    Coro::Fiber<> BehaviorCtrl::WaitDoneBehavior() const
    {
        co_await Coro::FiberUtil::WaitUntil([this] {
            return this->isDoneBehavior();
        });
    }
    void BehaviorCtrl::setup(Executer executer)
    {
        executer.on<IPostUpdate>().addBefore<StateCtrl>();
    }

    void BehaviorCtrl::onPostUpdate()
    {
        if (m_isActiveSeq) {
            m_sequence.resume();
        }

        if (m_isActiveBehavior) {
            m_behavior.resume();
        }
    }

    void BehaviorCtrl::onStateStart()
    {
        m_isActiveSeq = true;
        m_isActiveBehavior = false;
    }
}
