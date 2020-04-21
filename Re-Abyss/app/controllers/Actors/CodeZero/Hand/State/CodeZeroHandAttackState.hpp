#pragma once
#include "CodeZeroHandBaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss
{
    class CodeZeroHandAttackState final : public CodeZeroHandBaseState
    {
        bool m_isReturn = false;
    public:
        CodeZeroHandAttackState();
        void start()override;
        void update(double dt)override;
    };
}