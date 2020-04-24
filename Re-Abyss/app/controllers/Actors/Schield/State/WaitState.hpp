#pragma once
#include "BaseState.hpp"

namespace abyss::Schield
{
    class WaitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        WaitState();

        void update(double dt) override;
        void draw()const override;
        void onCollisionStay(ICollider* col) override;
    };
}
