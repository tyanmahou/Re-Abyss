#pragma once
#include <abyss/models/Actors/Enemy/DeadCallbackModel.hpp>

namespace abyss::Slime
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
    struct ComponentTree<Slime::DeadCallbackModel>
    {
        using Base = Enemy::DeadCallbackModel;
    };
}