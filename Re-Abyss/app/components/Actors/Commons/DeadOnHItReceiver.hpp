#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ICollisionCallback.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss::Actor
{
    class DeadOnHItReceiver :
        public IComponent,
        public ICollisionCallback
    {
        IActor* m_pActor;
        Ref<DeadChecker> m_deadChecker;
    public:
        DeadOnHItReceiver(IActor* pActor);
        void setup() override;
        void onCollisionStay(IActor* col)override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::DeadOnHItReceiver>
    {
        using Base = Actor::ICollisionCallback;
    };
}