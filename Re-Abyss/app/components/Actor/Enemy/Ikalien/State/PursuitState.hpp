#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    class PursuitState : public BaseState
    {
        TimerEx m_timer;
    public:
        PursuitState();
        void start()override;
        void update() override;

        void draw() const override;
    };
}