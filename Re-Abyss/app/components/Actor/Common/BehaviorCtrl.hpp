#pragma once

#include <memory>
#include <functional>

#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IPostUpdate.hpp>
#include <abyss/components/Actor/Common/IStateCallback.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>
#include <abyss/utils/Coro/AsyncGenerator/AsyncGenerator.hpp>

namespace abyss::Actor
{
    using BehaviorFunc = std::function<Coro::Fiber<>(ActorObj*)>;
    using BehaviorSeqFunc = std::function<Coro::AsyncGenerator<BehaviorFunc>(ActorObj*)>;

    class BehaviorCtrl final :
        public IComponent,
        public IPostUpdate,
        public IStateCallback
    {
    public:
        BehaviorCtrl(ActorObj* pActor);

        void setSequence(const BehaviorSeqFunc& sequence);
        void setBehavior(const BehaviorFunc& behavior);

        BehaviorCtrl& setActiveSequence(bool isActive)
        {
            m_isActiveSeq = isActive;
            return *this;
        }
        BehaviorCtrl& setActiveBehavior(bool isActive)
        {
            m_isActiveBehavior = isActive;
            return *this;
        }
        bool isDoneBehavior() const;

        Coro::Fiber<> WaitDoneBehavior() const;

    public:
        void setup(Executer executer)override;

        void onPostUpdate() override;

        void onStateStart() override;
    private:
        ActorObj* m_pActor = nullptr;
        Coro::FiberHolder<> m_sequence;
        Coro::FiberHolder<> m_behavior;

        bool m_isActiveSeq = true;
        bool m_isActiveBehavior = true;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<Actor::BehaviorCtrl>
    {
        using Base = MultiComponents<
            Actor::IPostUpdate,
            Actor::IStateCallback
        >;
    };
}