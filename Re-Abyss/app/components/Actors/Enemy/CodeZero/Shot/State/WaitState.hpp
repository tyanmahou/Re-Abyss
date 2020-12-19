#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class WaitState : public BaseState
    {
    public:
        Task<> start();

        void update() override;

        void draw() const;
    };
}