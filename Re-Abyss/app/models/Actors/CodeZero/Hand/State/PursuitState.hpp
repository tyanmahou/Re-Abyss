#pragma once
#include "BaseState.hpp"

namespace abyss::CodeZero::Hand
{
    class PursuitState final : public BaseState
    { 
    public:
        void update(double dt) override;
        void start()override;
    };
}