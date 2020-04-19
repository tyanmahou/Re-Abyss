#pragma once
#include "CodeZeroHandBaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss
{
    class CodeZeroHandAttackState final : public CodeZeroHandBaseState
    {
        bool m_isReturn = false;
        void updateRight(double dt) override;
        void updateLeft(double dt) override;
    public:
        CodeZeroHandAttackState();
        void start()override;
    };
}