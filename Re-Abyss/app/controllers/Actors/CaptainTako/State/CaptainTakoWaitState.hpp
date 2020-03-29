#pragma once
#include "CaptainTakoBaseState.hpp"

namespace abyss
{
    class CaptainTakoWaitState : public CaptainTakoBaseState
    {
        TimerEx m_waitTimer;
    public:
        CaptainTakoWaitState();
        void update(double dt) override;
        void draw()const override;
    };
}