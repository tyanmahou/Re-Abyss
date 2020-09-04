#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Schield
{
    class AttackPlusState final : public BaseState
    {
        TimerEx m_timer;
        TimerEx m_transitionToAttackPlus;
        TimerEx m_transitionToAttackCross;
        bool m_isAttack = false;
    public:
        AttackPlusState();

        void start();
        void update(double dt) override;

        void draw() const override;
    };
}
