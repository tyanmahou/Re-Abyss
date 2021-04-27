#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class AttackWaitState final : public BaseState
    {
    public:
        AttackWaitState();
        Task<> start()override;
        void update()override;
        void draw() const override;
    };
}