#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>
namespace abyss::Actor::Enemy::LaunShark
{
    class AttackState : public BaseState
    {
        TimerEx m_attackTimer;
    public:
        AttackState();
        Task<> start();
        void update() override;

        void draw() const override;
    };
}