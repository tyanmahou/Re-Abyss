#pragma once
#include "LaunSharkShotBaseState.hpp"

namespace abyss
{
    class LaunSharkShotWaitState final : public LaunSharkShotBaseState
    {
        TimerEx m_timer;
    public:
        LaunSharkShotWaitState();

        void update(double dt) override;
        void draw() const override;
    };
}