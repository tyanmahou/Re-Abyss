#pragma once

#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Slime
{

    class JumpState final: public BaseState
    {
    public:
        void start() override;
        void lastUpdate() override;

        void draw()const override;
    };
}