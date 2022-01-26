#pragma once
#include <abyss/components/Actor/Enemy/Schield/State/BaseState.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::Schield
{
    class WaitState final : public BaseState
    {
        TimeLite::Timer m_timer;
    public:
        WaitState();

        void start() override;
        void update() override;
        void end() override;
    };
}
