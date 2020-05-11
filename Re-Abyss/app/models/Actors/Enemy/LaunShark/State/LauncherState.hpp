#pragma once
#include "BaseState.hpp"

namespace abyss::LaunShark
{
    class LauncherState : public BaseState
    {
        TimerEx m_attackTimer;
        TimerEx m_waitTimer;
        bool m_out = false;
    public:
        LauncherState();
        void start();
        void update(double dt) override;
        void draw()const override;
    };
}