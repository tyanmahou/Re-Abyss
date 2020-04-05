#pragma once
#include "LaunSharkBaseState.hpp"

namespace abyss
{
    class LaunSharkSwimState : public LaunSharkBaseState
    {
        TimerEx m_waitTimer;

        void onCollisionMap(ColDirection col) override;
    public:
        LaunSharkSwimState();
        void start();
        void update(double dt) override;
        void draw()const override;
    };
}