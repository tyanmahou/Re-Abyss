#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    class ChargeState : public BaseState
    {
        TimerEx m_chargeTimer;
    public:
        ChargeState();
        void start() override;
        Task<> task() override;
        void update() override;
    };
}