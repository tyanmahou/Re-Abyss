#pragma once

#include "SlimeBaseState.hpp"

namespace abyss
{

    class SlimeJumpState final: public SlimeBaseState
    {
        void onColisionMapUp() override;
    public:
        void start() override;

        void draw() const override;
    };
}