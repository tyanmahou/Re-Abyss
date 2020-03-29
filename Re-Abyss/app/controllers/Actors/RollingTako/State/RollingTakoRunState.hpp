#pragma once
#include "RollingTakoBaseState.hpp"

namespace abyss
{
    class RollingTakoRunState : public RollingTakoBaseState
    {
    public:
        void update(double dt) override;
        void draw()const override;
    };
}