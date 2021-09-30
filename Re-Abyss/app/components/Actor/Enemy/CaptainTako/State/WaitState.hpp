#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    class WaitState : public BaseState
    {
        TimeLite::Timer m_waitTimer;
    public:
        WaitState();
        void start() override;
        void update() override;
    };
}