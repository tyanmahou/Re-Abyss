#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::CodeZero::Shot
{
    class PursuitState : public BaseState
    {
        TimerEx m_timer;
    public:
        PursuitState();

        void update(double dt);
    };
}