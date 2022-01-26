#pragma once
#include <abyss/components/Actor/Player/State/BaseState.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
namespace abyss::Actor::Player
{
    class DeadState final : public BaseState
    {
        void start()override;
        void update()override;
    public:
        DeadState();
    private:
        TimeLite::Timer m_deadTimer;
    };
}