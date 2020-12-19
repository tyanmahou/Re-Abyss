#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Schield
{
    class WaitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        WaitState();

        Task<> start() override;
        void update() override;
        void end() override;

        void draw() const override;
    };
}
