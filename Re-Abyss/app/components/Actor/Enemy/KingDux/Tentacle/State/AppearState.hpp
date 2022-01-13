#pragma once
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/BaseState.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    class AppearState final :
        public BaseState
    {
    public:
        AppearState();
        void start() override;
        void update() override;
    private:
        TimeLite::Timer m_moveTimer{ 1.5 };
    };
}