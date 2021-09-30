#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::Schield
{
    class AttackCrossState final : public BaseState
    {
        TimeLite::Timer m_timer;
        TimeLite::Timer m_transitionToWait;
        bool m_isAttack = false;
    public:
        AttackCrossState();
        void start();
        void update() override;
    };
}
