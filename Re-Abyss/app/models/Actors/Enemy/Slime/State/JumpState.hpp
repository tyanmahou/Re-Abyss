#pragma once

#include "BaseState.hpp"

namespace abyss::Slime
{

    class JumpState final: public BaseState
    {
    public:
        void start() override;

        void draw() const override;

        void lastUpdate(double dt) override;
    };
}