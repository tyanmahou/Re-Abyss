#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class WaitState final :
        public BaseState
    {
    public:
        void start() override;
    };
}