#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    class WaitState : public BaseState
    {
        TimerEx m_waitTimer;
    public:
        WaitState();
        void start() override;
        void update(double dt) override;
        void draw() const override;
    };
}