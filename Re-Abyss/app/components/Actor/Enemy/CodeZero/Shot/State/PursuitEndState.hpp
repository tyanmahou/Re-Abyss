#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class PursuitEndState : public BaseState
    {
        TimerEx m_timer;
    public:
        PursuitEndState();
        Task<> start();
        void update() override;
    };
}