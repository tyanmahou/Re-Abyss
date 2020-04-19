#pragma once
#include "CodeZeroHandBaseState.hpp"

namespace abyss
{
    class CodeZeroHandPursuitState final : public CodeZeroHandBaseState
    { 
        void updateRight(double dt) override;
        void updateLeft(double dt) override;
    public:
        void start()override;
    };
}