#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class AttackState final : public BaseState
    {
        bool m_isReturn = false;
    public:
        AttackState();
        Task<> start()override;
        void update()override;
    };
}