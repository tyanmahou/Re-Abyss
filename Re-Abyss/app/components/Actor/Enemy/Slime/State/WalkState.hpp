#pragma once
#include <abyss/components/Actor/Enemy/Slime/State/BaseState.hpp>

namespace abyss::Actor::Enemy::Slime
{

    class WalkState final : public BaseState
    {
    public:
        void start() override;

        void update() override;
        void lastUpdate() override;
    };
}