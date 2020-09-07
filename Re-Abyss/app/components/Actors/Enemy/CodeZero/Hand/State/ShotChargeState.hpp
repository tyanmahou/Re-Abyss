#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class ShotChargeState final : public BaseState
    {
    public:
        ShotChargeState();
        void start()override;
        void update(double dt)override;
    };
}