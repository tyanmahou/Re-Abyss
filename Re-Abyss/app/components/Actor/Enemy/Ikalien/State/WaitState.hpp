#pragma once
#include <abyss/components/Actor/Enemy/Ikalien/State/BaseState.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    class WaitState : public BaseState
    {
    public:
        void start()override;
        void update() override;
    };
}