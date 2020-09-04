#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero
{
    class Phase1State : public BaseState
    {   
    public:
        Phase1State();
        void start();
        void update(double dt) override;
    };
}