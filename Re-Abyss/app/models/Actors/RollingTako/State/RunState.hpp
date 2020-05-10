#pragma once
#include "BaseState.hpp"

namespace abyss::RollingTako
{
    class RunState : public BaseState
    {
    public:
        void update(double dt) override;
        void draw()const override;
    };
}