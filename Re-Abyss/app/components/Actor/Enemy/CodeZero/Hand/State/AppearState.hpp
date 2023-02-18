#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class AppearState final : public BaseState
    {
    public:
        AppearState();
        void start()override;
        void end() override;
        void update()override;
    };
}
