#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Schield
{
    class WaitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        WaitState();

        void start() override;
        void update() override;
        void end() override;
    };
}
