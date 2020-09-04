#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor::CodeZero::Hand
{
    class AttackState final : public BaseState
    {
        bool m_isReturn = false;
    public:
        AttackState();
        void start()override;
        void update(double dt)override;
    };
}