#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Schield
{
    class AttackCrossState final : public BaseState
    {
        TimerEx m_timer;
        TimerEx m_transitionToWait;
        bool m_isAttack = false;
    public:
        AttackCrossState();
        Task<> start();
        void update() override;

        void draw() const override;
    };
}
