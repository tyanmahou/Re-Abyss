#pragma once
#include "LaunSharkShotBaseState.hpp"

namespace abyss
{
    class LaunSharkShotPursuitState final : public LaunSharkShotBaseState
    {
        TimerEx m_timer;
    public:
        LaunSharkShotPursuitState();

        void update(double dt) override;
        void draw() const override;
    };
}