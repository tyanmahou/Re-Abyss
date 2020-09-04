#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    class StartState : public BaseState
    {
    public:
        void start()override;
        void update(double dt) override;

        void draw() const override;
    };
}