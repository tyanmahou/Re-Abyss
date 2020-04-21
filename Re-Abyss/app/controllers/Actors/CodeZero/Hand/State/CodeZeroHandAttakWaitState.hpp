#pragma once
#include "CodeZeroHandBaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss
{
    class CodeZeroHandAttackWaitState final : public CodeZeroHandBaseState
    {
        TimerEx m_timer;
    public:
        CodeZeroHandAttackWaitState();
        void start()override;
        void update(double dt)override;
        void draw() const override;
    };
}