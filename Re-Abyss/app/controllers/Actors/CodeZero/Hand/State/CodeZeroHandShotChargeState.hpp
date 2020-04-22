#pragma once
#include "CodeZeroHandBaseState.hpp"

namespace abyss
{
    class CodeZeroHandShotChargeState final : public CodeZeroHandBaseState
    {
    public:
        CodeZeroHandShotChargeState();
        void start()override;
        void update(double dt)override;
    };
}