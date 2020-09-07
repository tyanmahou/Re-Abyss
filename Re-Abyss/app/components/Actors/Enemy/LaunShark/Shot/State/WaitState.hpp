#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    class WaitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        WaitState();
        void start() override;
        void update(double dt) override;

        void draw() const override;
    };
}