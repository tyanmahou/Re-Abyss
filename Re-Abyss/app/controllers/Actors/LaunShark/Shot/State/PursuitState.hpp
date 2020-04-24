#pragma once
#include "BaseState.hpp"

namespace abyss::LaunShark::Shot
{
    class PursuitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        PursuitState();

        void update(double dt) override;
        void draw() const override;
    };
}