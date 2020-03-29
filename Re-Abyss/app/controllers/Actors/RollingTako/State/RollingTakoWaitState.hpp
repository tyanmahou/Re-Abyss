#pragma once
#include "RollingTakoBaseState.hpp"

namespace abyss
{
    class RollingTakoWaitState : public RollingTakoBaseState
    {
    public:
        void update(double dt) override;
        void draw()const override;
    };
}