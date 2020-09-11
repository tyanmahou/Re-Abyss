#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IDeadCallback.hpp>

namespace abyss::Actor::Enemy
{
    class DeadCallback :
        public IComponent,
        public IDeadCallback
    {
    protected:
        IActor* m_pActor;
        bool m_useQuake = true;
    public:
        DeadCallback(IActor* pActor);

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