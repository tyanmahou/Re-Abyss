#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/IDeadCallback.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class DeadCallback :
        public IComponent,
        public IDeadCallback
    {
    public:
        DeadCallback(ActorObj* pActor);

        void onDead() override;

    private:
        ActorObj* m_pActor;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::KingDux::DeadCallback>
    {
        using Base = Actor::IDeadCallback;
    };
}