#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::CodeZero::Shot
{
    class PursuitEndState : public BaseState
    {
        TimerEx m_timer;
    public:
        PursuitEndState();
        void start();
        void update(double dt);
    };
}