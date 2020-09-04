#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>
namespace abyss::Actor::LaunShark
{
    class AttackState : public BaseState
    {
        TimerEx m_attackTimer;
    public:
        AttackState();
        void start();
        void update(double dt) override;

        void draw() const override;
    };
}