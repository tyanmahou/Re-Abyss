#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/BaseState.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class PursuitState : public BaseState
    {
        TimeLite::Timer m_timer;
    public:
        PursuitState();
        void start();
        void update() override;
    };
}