#pragma once
#include "LaunSharkBaseState.hpp"

namespace abyss
{
    class LaunSharkAttackState : public LaunSharkBaseState
    {
        TimerEx m_attackTimer;
    public:
        LaunSharkAttackState();
        void start();
        void update(double dt) override;
        void draw()const override;
    };
}