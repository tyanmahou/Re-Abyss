#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class AngryState final : public BaseState
    {
    public:
        AngryState();
        void start()override;
        void end() override;
        void update()override;
    };
}
