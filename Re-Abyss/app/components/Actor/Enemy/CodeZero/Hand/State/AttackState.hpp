#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class AttackState final : public BaseState
    {
    public:
        AttackState();
        void start()override;
        void update()override;
    };
}