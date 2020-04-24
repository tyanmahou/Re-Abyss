#pragma once
#include "BaseState.hpp"

namespace abyss::CaptainTako
{
    class ChargeState : public BaseState
    {
        TimerEx m_chargeTimer;
    public:
        ChargeState();
        void update(double dt) override;
        void draw()const override;
    };
}