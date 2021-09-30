#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::Schield
{
    class AttackPlusState final : public BaseState
    {
        TimeLite::Timer m_timer;
        TimeLite::Timer m_transitionToAttackPlus;
        TimeLite::Timer m_transitionToAttackCross;
        bool m_isAttack = false;
    public:
        AttackPlusState();

        void start();
        void update() override;
    };
}
