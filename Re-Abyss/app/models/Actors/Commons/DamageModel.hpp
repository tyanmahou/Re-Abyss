#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/ICollisionCallbackModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss
{
    class DamageModel : 
        public IComponent,
        public ICollisionCallbackModel
    {
    protected:
        Ref<HPModel> m_hp;
        IActor* m_pActor;
    public:
        DamageModel(IActor* pActor);

        void setup() override;
        void onCollisionStay(IActor* col)override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<DamageModel>
    {
        using Base = ICollisionCallbackModel;
    };
}