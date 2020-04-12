#pragma once
#include "SchieldBaseState.hpp"

namespace abyss
{
    class SchieldWaitState final : public SchieldBaseState
    {
        TimerEx m_timer;
    public:
        SchieldWaitState();


        void update(double dt) override;
        void draw()const override;
        void onCollisionStay(ICollider* col) override;
    };
}
