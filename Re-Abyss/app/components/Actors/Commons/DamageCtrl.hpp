#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/ICollisionCallbackModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss::Actor
{
    class DamageCtrl : 
        public IComponent,
        public ICollisionCallbackModel
    {
    protected:
        Ref<HPModel> m_hp;
        IActor* m_pActor;
    public:
        DamageCtrl(IActor* pActor);

        void setup() override;
        void onCollisionStay(IActor* col)override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::DamageCtrl>
    {
        using Base = ICollisionCallbackModel;
    };
}