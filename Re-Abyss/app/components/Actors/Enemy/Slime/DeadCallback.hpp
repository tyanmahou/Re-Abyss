#pragma once
#include <abyss/components/Actors/Enemy/DeadCallback.hpp>

namespace abyss::Actor::Enemy::Slime
{
    class DeadCallback : public Enemy::DeadCallback
    {
    public:
        using Enemy::DeadCallback::DeadCallback;
        void onDead() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::Slime::DeadCallback>
    {
        using Base = Actor::Enemy::DeadCallback;
    };
}