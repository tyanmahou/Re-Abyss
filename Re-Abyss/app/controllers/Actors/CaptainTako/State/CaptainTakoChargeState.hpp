#pragma once
#include "CaptainTakoBaseState.hpp"

namespace abyss
{
    class CaptainTakoChargeState : public CaptainTakoBaseState
    {
        TimerEx m_chargeTimer;
    public:
        CaptainTakoChargeState();
        void update(double dt) override;
        void draw()const override;
    };
}