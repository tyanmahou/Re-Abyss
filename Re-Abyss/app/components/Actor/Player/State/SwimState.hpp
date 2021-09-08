#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class SwimState final : public BaseState
    {
    private:
        void onLanding()override;

        void start() override;
        void update()override;
        void lastUpdate()override;
    };
}