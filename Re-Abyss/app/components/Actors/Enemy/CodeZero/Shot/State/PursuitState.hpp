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
        Task<> start();
        void update() override;
    };
}