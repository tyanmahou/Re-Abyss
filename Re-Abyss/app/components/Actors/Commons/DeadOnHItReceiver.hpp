#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ICollisionReact.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss::Actor
{
    class DeadOnHItReceiver :
        public IComponent,
        public ICollisionReact
    {
        IActor* m_pActor;
        Ref<DeadChecker> m_deadChecker;
        Ref<CollisionCtrl> m_cols;
    public:
        DeadOnHItReceiver(IActor* pActor);
        void onStart() override;
        void onCollisionReact()override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::DeadOnHItReceiver>
    {
        using Base = Actor::ICollisionReact;
    };
}