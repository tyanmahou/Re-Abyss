#pragma once
#include "SchieldBaseState.hpp"

namespace abyss
{
    class SchieldAttackCrossState final : public SchieldBaseState
    {
        TimerEx m_timer;
        TimerEx m_transitionToWait;
        bool m_isAttack = false;
    public:
        SchieldAttackCrossState();


        void update(double dt) override;
        void draw()const override;
    };
}
