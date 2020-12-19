#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class AttackWaitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        AttackWaitState();
        Task<> start()override;
        void update()override;
        void draw() const override;
    };
}