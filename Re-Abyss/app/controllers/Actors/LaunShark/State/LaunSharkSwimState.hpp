#pragma once
#include "LaunSharkBaseState.hpp"

namespace abyss
{
    class LaunSharkSwimState : public LaunSharkBaseState
    {
        double m_totalTime = 0;
    public:
        void update(double dt) override;
        void draw()const override;
    };
}