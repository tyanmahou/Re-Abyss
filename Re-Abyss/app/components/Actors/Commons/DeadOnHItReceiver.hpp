#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/ICollisionCallbackModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss::Actor
{
    class DeadOnHItReceiver :
        public IComponent,
        public ICollisionCallbackModel
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
        using Base = ICollisionCallbackModel;
    };
}