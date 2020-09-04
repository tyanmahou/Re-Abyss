#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class WaitState : public BaseState
    {
    public:
        void start();

        void update(double dt);

        void draw() const;
    };
}