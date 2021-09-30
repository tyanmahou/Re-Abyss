#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    class LauncherState : public BaseState
    {
        TimeLite::Timer m_attackTimer;
        TimeLite::Timer m_waitTimer;
        bool m_out = false;
    public:
        LauncherState();
        void start();
        void update() override;
        void end();
    };
}