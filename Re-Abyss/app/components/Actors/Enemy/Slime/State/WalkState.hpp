#pragma once

#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Slime
{

    class WalkState final : public BaseState
    {
    public:
        Task<> start() override;

        void update() override;

        void draw()const override;
    };
}