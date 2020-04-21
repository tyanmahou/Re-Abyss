#pragma once
#include "CodeZeroHandBaseState.hpp"

namespace abyss
{
    class CodeZeroHandPursuitState final : public CodeZeroHandBaseState
    { 
    public:
        void update(double dt) override;
        void start()override;
    };
}