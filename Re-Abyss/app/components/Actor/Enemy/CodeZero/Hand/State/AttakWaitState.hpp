#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class AttackWaitState final : public BaseState
    {
    public:
        AttackWaitState();
        void start() override;
        void end() override;
        Task<> task()override;
        void update()override;
    };
}