#pragma once

#include "BaseState.hpp"

namespace abyss::Slime
{

    class JumpState final: public BaseState
    {
        void onColisionMapUp() override;
    public:
        void start() override;

        void draw() const override;
    };
}