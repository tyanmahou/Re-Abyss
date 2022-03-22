#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class AppearState final :
        public BaseState
    {
    public:
        void start() override;
        void end() override;
        Coro::Task<> task() override;
        void update() override;
    private:
    };
}