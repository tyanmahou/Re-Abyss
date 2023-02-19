#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class AngryEndState final : public BaseState
    {
    public:
        AngryEndState();
        void start()override;
        void end() override;
        Fiber<> task()override;
        void update()override;
    };
}
