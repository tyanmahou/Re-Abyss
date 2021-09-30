#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    class AttackState : public BaseState
    {
        TimeLite::Timer m_attackTimer;
    public:
        AttackState();
        void start();
        void update() override;
    };
}