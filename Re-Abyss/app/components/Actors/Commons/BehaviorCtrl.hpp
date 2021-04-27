#pragma once

#include <memory>
#include <functional>

#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IUpdate.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Actor
{
    class BehaviorCtrl final : 
        public IComponent,
        public IUpdate
    {
        ActorObj* m_pActor = nullptr;
        std::unique_ptr<Coro::Task<>> m_task = nullptr;

        bool m_isActive = true;
    public:
        BehaviorCtrl(ActorObj* pActor);

        void setBehavior(std::function<Coro::Task<>(ActorObj*)> behavior);

        void onUpdate() override;

        BehaviorCtrl& setActive(bool isActive)
        {
            m_isActive = isActive;
            return *this;
        }
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