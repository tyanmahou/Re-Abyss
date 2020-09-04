#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::CodeZero::Hand
{
    class PursuitState final : public BaseState
    { 
    public:
        void update(double dt) override;
        void start()override;
        void lastUpdate() override;
    };
}