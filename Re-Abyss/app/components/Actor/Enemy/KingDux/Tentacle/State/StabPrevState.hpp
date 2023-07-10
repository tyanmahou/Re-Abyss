#pragma once
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    class StabPrevState final :
        public BaseState
    {
    public:
        void start() override;
        void end() override;
        Coro::Fiber<> updateAsync() override;
    };
}
