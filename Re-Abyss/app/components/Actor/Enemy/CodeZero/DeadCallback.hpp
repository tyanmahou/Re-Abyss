#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/IDeadCallback.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class DeadCallback :
        public IComponent,
        public IDeadCallback
    {
    public:
        DeadCallback(ActorObj* pActor);
    public:
        void onDead() override;

    private:
        ActorObj* m_pActor;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::DeadCallback>
    {
        using Base = Actor::IDeadCallback;
    };
}
