#pragma once
#include"BaseState.hpp"

namespace abyss::Player
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

        void onCollisionStay(const PenetrateFloorActor& col) override;
        void onCollisionStay(const DoorActor& col) override;

        void start() override;
        void update(double dt)override;
        void lastUpdate()override;
        void onDraw(const PlayerVM& view)const override;
    };
}