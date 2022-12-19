#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/IDamageCallback.hpp>
#include <abyss/components/Actor/Common/IDeadCallback.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    class DamageCallback :
        public IComponent,
        public IDamageCallback,
        public IDeadCallback
    {
    public:
        DamageCallback(ActorObj* pActor);
    public:
        void onStart() override;
    public:
        void onDamaged(const DamageData& damage) override;
    public:
        void onDead() override;
    private:
        ActorObj* m_pActor;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Gimmick::ShutterWall::DamageCallback>
    {
        using Base = MultiComponents<
            Actor::IDamageCallback,
            Actor::IDeadCallback
        >;
    };
}
