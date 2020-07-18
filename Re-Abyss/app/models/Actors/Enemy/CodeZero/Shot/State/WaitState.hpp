#pragma once
#include "BaseState.hpp"

namespace abyss::CodeZero::Shot
{
    class WaitState : public BaseState
    {
    public:
        void start();

        void update(double dt);

        void end();
    };
}