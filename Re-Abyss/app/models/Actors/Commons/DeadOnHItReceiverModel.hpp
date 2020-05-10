#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
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
        bool m_isAutoDestroy = true;
    public:
        DeadOnHItReceiverModel(IActor* pActor);
        DeadOnHItReceiverModel& setAutoDestroy(bool isAuto);
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