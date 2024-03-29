#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/IDeadCallback.hpp>

namespace abyss::Actor::Enemy
{
    class DeadCallback :
        public IComponent,
        public IDeadCallback
    {
    protected:
        ActorObj* m_pActor;
        bool m_useQuake = true;
    public:
        DeadCallback(ActorObj* pActor);

        void onDead() override;

        void setUseQuake(bool useQuake)
        {
            m_useQuake = useQuake;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::DeadCallback>
    {
        using Base = Actor::IDeadCallback;
    };
}