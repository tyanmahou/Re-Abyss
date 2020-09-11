#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IDamageCallback.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy
{
    class DamageCallback :
        public IComponent,
        public IDamageCallback
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
        using Base = Actor::IDamageCallback;
    };
}