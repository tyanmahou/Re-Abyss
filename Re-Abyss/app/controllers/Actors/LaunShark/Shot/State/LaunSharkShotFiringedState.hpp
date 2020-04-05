#pragma once
#include "LaunSharkShotBaseState.hpp"

namespace abyss
{
    class LaunSharkShotFiringedState final : public LaunSharkShotBaseState
    {
    public:
        void start();
        void update(double dt) override;
        void draw() const override;
    };
}