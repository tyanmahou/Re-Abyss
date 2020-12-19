#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    class WaitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        WaitState();
        Task<> start() override;
        void update() override;

        void draw() const override;
    };
}