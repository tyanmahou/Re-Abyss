#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class AttackState final : public BaseState
    {
    public:
        AttackState();
        void start()override;
        void update()override;
    };
}