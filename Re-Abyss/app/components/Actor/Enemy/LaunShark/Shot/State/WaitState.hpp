#pragma once
#include <abyss/components/Actor/Enemy/LaunShark/Shot/State/BaseState.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    class WaitState final : public BaseState
    {
        TimeLite::Timer m_timer;
    public:
        WaitState();
        void start() override;
        void update() override;
    };
}