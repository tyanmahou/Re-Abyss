#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class RollingAttackState final : public BaseState
    {
    public:
        RollingAttackState();
        void start()override;
        void update()override;
    };
}