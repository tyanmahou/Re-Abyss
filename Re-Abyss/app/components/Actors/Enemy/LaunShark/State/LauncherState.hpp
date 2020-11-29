#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    class LauncherState : public BaseState
    {
        TimerEx m_attackTimer;
        TimerEx m_waitTimer;
        bool m_out = false;
    public:
        LauncherState();
        void start();
        void update() override;
        void end();

        void draw() const;
    };
}