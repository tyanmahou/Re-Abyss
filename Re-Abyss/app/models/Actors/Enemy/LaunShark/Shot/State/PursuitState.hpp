#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::LaunShark::Shot
{
    class PursuitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        PursuitState();

        void start() override;
        void update(double dt) override;

        void draw()const override;
    };
}