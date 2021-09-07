#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::RollingTako
{
    class WaitState : public BaseState
    {
    public:
        void start()override;
        void update() override;
    };
}