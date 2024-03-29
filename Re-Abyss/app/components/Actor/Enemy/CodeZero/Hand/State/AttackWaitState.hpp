#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class AttackWaitState final : public BaseState
    {
    public:
        AttackWaitState();
        void start() override;
        void end() override;
        Fiber<> updateAsync()override;
        void update()override;
    };
}
