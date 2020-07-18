#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::CaptainTako
{
    class ChargeState : public BaseState
    {
        TimerEx m_chargeTimer;
    public:
        ChargeState();
        void start() override;
        void update(double dt) override;
    };
}