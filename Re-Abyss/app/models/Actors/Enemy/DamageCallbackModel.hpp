#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDamageCallbackModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy
{
    class DamageCallbackModel :
        public IComponent,
        public IDamageCallbackModel
    {
    protected:
        IActor* m_pActor;
    public:
        DamageCallbackModel(IActor* pActor);

        void setup();
        void onDamaged() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::DamageCallbackModel>
    {
        using Base = IDamageCallbackModel;
    };
}