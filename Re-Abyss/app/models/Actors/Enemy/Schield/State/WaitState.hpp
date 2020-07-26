#pragma once
#include "BaseState.hpp"

namespace abyss::Schield
{
    class WaitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        WaitState();

        void start() override;
        void update(double dt) override;
        void end() override;

        void draw() const override;
    };
}
