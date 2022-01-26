#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class ShotChargeState final : public BaseState
    {
    public:
        ShotChargeState();
        void start()override;
        void update()override;
    };
}