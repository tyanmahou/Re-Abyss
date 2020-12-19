#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Schield
{
    class AttackPlusState final : public BaseState
    {
        TimerEx m_timer;
        TimerEx m_transitionToAttackPlus;
        TimerEx m_transitionToAttackCross;
        bool m_isAttack = false;
    public:
        AttackPlusState();

        Task<> start();
        void update() override;

        void draw() const override;
    };
}
