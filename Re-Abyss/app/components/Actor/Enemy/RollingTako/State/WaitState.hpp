#pragma once
#include <abyss/components/Actor/Enemy/RollingTako/State/BaseState.hpp>

namespace abyss::Actor::Enemy::RollingTako
{
    class WaitState : public BaseState
    {
    public:
        void start()override;
        void update() override;
    };
}