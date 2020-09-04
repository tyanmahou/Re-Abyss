#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::CodeZero::Shot
{
    class WaitState : public BaseState
    {
    public:
        void start();

        void update(double dt);

        void draw() const;
    };
}