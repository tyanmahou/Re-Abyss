#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/ICollisionCallbackModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss
{
    class DeadOnHItReceiverModel :
        public IComponent,
        public ICollisionCallbackModel
    {
        IActor* m_pActor;
        Ref<DeadCheckerModel> m_deadChecker;
    public:
        DeadOnHItReceiverModel(IActor* pActor);
        void setup() override;
        void onCollisionStay(IActor* col)override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<DeadOnHItReceiverModel>
    {
        using Base = ICollisionCallbackModel;
    };
}