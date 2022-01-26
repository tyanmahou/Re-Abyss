#pragma once
#include <abyss/components/Actor/Enemy/LaunShark/Shot/State/BaseState.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    class StartState : public BaseState
    {
    public:
        void start()override;
        void update() override;
    };
}