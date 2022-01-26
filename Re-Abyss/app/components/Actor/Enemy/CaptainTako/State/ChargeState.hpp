#pragma once
#include <abyss/components/Actor/Enemy/CaptainTako/State/BaseState.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    class ChargeState : public BaseState
    {
        TimeLite::Timer m_chargeTimer;
    public:
        ChargeState();
        void start() override;
        Task<> task() override;
        void update() override;
    };
}