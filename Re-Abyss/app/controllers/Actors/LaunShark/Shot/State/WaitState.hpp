#pragma once
#include "BaseState.hpp"

namespace abyss::LaunShark::Shot
{
    class WaitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        WaitState();

        void update(double dt) override;
        void draw() const override;
    };
}