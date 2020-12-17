#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class SwimState final : public BaseState
    {
        enum class Motion
        {
            Stay,
            Swim,
            Run,
            Float,
            Dive,
            Door,
            Ladder,
        };

    private:
        Motion m_motion = Motion::Stay;
    private:
        void onLanding()override;

        bool onCollisionStay(const PenetrateFloorProxy& col) override;
        bool onCollisionStay(const DoorProxy& col) override;

        void start() override;
        void update()override;
        void lastUpdate()override;
        void onDraw(const PlayerVM& view)const override;
    };
}