#pragma once

#include <memory>
#include <functional>

#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IUpdate.hpp>
#include <abyss/components/Actor/Common/IStateCallback.hpp>
#include <abyss/utils/Coro/Task/TaskHolder.hpp>

namespace abyss::Actor
{
    class BehaviorCtrl final : 
        public IComponent,
        public IUpdate,
        public IStateCallback
    {
    public:
        BehaviorCtrl(ActorObj* pActor);

        void setSequence(std::function<Coro::Task<>(ActorObj*)> sequence);
        void setBehavior(std::function<Coro::Task<>(ActorObj*)> behavior);

        void onUpdate() override;

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

        void onStateStart() override;
    private:
        ActorObj* m_pActor = nullptr;
        Coro::TaskHolder<> m_sequence;
        Coro::TaskHolder<> m_behavior;

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
            Actor::IUpdate,
            Actor::IStateCallback
        >;
    };
}