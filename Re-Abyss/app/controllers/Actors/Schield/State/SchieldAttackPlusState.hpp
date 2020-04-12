#pragma once
#include "SchieldBaseState.hpp"

namespace abyss
{
    class SchieldAttackPlusState final : public SchieldBaseState
    {
        TimerEx m_timer;
        TimerEx m_transitionToAttackPlus;
        TimerEx m_transitionToAttackCross;
        bool m_isAttack = false;
    public:
        SchieldAttackPlusState();


        void update(double dt) override;
        void draw()const override;
    };
}
