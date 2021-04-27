#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class ShotChargeState final : public BaseState
    {
    public:
        ShotChargeState();
        Task<> start()override;
        void update()override;
    };
}