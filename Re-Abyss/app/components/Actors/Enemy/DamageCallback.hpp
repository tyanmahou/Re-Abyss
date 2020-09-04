#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDamageCallbackModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy
{
    class DamageCallback :
        public IComponent,
        public IDamageCallbackModel
    {
    protected:
        IActor* m_pActor;
    public:
        DamageCallback(IActor* pActor);

        void setup();
        void onDamaged() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::DamageCallback>
    {
        using Base = IDamageCallbackModel;
    };
}