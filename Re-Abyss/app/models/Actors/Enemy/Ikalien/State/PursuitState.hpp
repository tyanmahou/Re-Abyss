#pragma once
#include "BaseState.hpp"

namespace abyss::Ikalien
{
    class PursuitState : public BaseState
    {
        TimerEx m_timer;
    public:
        PursuitState();
        void start()override;
        void update(double dt) override;
    };
}