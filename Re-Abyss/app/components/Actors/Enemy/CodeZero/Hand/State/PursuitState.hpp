#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class PursuitState final : public BaseState
    { 
    public:
        void update(double dt) override;
        void start()override;
        void lastUpdate() override;
    };
}