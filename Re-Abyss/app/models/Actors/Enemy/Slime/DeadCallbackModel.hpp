#pragma once
#include <abyss/models/Actors/Enemy/DeadCallbackModel.hpp>

namespace abyss::Actor::Enemy::Slime
{
    class DeadCallbackModel : public Enemy::DeadCallbackModel
    {
    public:
        using Enemy::DeadCallbackModel::DeadCallbackModel;
        void onDead() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::Slime::DeadCallbackModel>
    {
        using Base = Actor::Enemy::DeadCallbackModel;
    };
}