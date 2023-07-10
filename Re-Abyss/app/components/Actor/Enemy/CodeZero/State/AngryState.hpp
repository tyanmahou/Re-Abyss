#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class AngryState final :
        public BaseState
    {
    public:
        void start() override;
        void end() override;

        Coro::Fiber<> updateAsync() override;

        void update() override;
    private:
    };
}
