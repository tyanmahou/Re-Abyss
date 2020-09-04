#pragma once
#include <abyss/components/Actors/Enemy/DeadCallback.hpp>

namespace abyss::Actor::Enemy::Slime
{
    class DeadCallbackModel : public Enemy::DeadCallback
    {
    public:
        using Enemy::DeadCallback::DeadCallback;
        void onDead() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::Slime::DeadCallbackModel>
    {
        using Base = Actor::Enemy::DeadCallback;
    };
}