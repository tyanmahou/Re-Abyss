#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/IDamageCallback.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy
{
    class DamageCallback :
        public IComponent,
        public IDamageCallback
    {
    protected:
        ActorObj* m_pActor;
    public:
        DamageCallback(ActorObj* pActor);

        void setup();
        void onDamaged(const DamageData& damage) override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::DamageCallback>
    {
        using Base = Actor::IDamageCallback;
    };
}