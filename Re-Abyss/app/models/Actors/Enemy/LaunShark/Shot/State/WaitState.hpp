#pragma once
#include "BaseState.hpp"

namespace abyss::LaunShark::Shot
{
    class WaitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        WaitState();
        void start() override;
        void update(double dt) override;
    };
}