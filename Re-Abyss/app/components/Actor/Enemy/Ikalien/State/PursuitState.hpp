#pragma once
#include <abyss/components/Actor/Enemy/Ikalien/State/BaseState.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    class PursuitState : public BaseState
    {
        TimeLite::Timer m_timer;
    public:
        PursuitState();
        void start()override;
        void update() override;
    };
}