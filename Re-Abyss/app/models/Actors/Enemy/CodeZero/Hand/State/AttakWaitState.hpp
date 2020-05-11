#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::CodeZero::Hand
{
    class AttackWaitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        AttackWaitState();
        void start()override;
        void update(double dt)override;
        void draw() const override;
    };
}