#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    class SwimState : public BaseState
    {
        TimerEx m_waitTimer;

    public:
        SwimState();
        void start();
        void update(double dt) override;
        void lastUpdate() override;

        void draw() const override;
    };
}