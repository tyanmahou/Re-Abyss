#pragma once
#include "BaseState.hpp"

namespace abyss::CaptainTako
{
    class WaitState : public BaseState
    {
        TimerEx m_waitTimer;
    public:
        WaitState();
        void update(double dt) override;
        void draw()const override;
    };
}