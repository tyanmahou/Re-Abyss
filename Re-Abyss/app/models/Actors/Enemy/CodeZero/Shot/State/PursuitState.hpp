#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class PursuitState : public BaseState
    {
        TimerEx m_timer;
    public:
        PursuitState();
        void start();
        void update(double dt);
    };
}