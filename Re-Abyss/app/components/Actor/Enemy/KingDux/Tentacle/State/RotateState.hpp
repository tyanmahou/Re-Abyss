#pragma once
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/BaseState.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    class RotateState final :
        public BaseState
    {
    public:
        void start() override;
        void update() override;
    private:
    };
}