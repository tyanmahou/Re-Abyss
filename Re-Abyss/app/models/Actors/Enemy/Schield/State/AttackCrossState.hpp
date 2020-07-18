#pragma once
#include "BaseState.hpp"

namespace abyss::Schield
{
    class AttackCrossState final : public BaseState
    {
        TimerEx m_timer;
        TimerEx m_transitionToWait;
        bool m_isAttack = false;
    public:
        AttackCrossState();
        void start();
        void update(double dt) override;
    };
}
