#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IDamageCallback.hpp>

namespace abyss::Actor::Player
{
    class DamageCallback :
        public IComponent,
        public IDamageCallback
    {
    public:
        DamageCallback(ActorObj* pActor);

        void onDamaged(const DamageData& damage) override;

    private:
        ActorObj* m_pActor;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::DamageCallback>
    {
        using Base = Actor::IDamageCallback;
    };
}