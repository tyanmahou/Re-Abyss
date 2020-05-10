#pragma once
#include "BaseState.hpp"

namespace abyss::LaunShark
{
    class AttackState : public BaseState
    {
        TimerEx m_attackTimer;
    public:
        AttackState();
        void start();
        void update(double dt) override;
        void draw()const override;
    };
}