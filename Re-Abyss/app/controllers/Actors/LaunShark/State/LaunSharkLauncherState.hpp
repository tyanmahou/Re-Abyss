#pragma once
#include "LaunSharkBaseState.hpp"

namespace abyss
{
    class LaunSharkLauncherState : public LaunSharkBaseState
    {
        TimerEx m_attackTimer;
        TimerEx m_waitTimer;
        bool m_out = false;
    public:
        LaunSharkLauncherState();
        void start();
        void update(double dt) override;
        void draw()const override;
    };
}