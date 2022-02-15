#pragma once

#include <memory>
#include <functional>

#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IUpdate.hpp>
#include <abyss/utils/Coro/Task/TaskHolder.hpp>

namespace abyss::Actor
{
    class BehaviorCtrl final : 
        public IComponent,
        public IUpdate
    {
    public:
        BehaviorCtrl(ActorObj* pActor);

        void setSequence(std::function<Coro::Task<>(ActorObj*)> sequence);
        void setBehavior(std::function<Coro::Task<>(ActorObj*)> behavior);

        void onUpdate() override;

        BehaviorCtrl& setActive(bool isActive)
        {
            m_isActive = isActive;
            return *this;
        }
    private:
        ActorObj* m_pActor = nullptr;
        Coro::TaskHolder<> m_sequence;
        Coro::TaskHolder<> m_task;

        bool m_isActive = true;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<Actor::BehaviorCtrl>
    {
        using Base = Actor::IUpdate;
    };
}