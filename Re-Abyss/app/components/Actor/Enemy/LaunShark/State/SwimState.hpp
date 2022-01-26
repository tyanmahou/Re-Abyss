#pragma once
#include <abyss/components/Actor/Enemy/LaunShark/State/BaseState.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    class SwimState : public BaseState
    {
        TimeLite::Timer m_waitTimer;

    public:
        SwimState();
        void start();
        void update() override;
        void lastUpdate() override;
    };
}