#pragma once
#include "BaseState.hpp"

namespace abyss::LaunShark
{
    class SwimState : public BaseState
    {
        TimerEx m_waitTimer;

        void onCollisionMap(ColDirection col) override;
    public:
        SwimState();
        void start();
        void update(double dt) override;
        void draw()const override;
    };
}