#pragma once
#include"PlayerBaseState.hpp"

namespace abyss
{
    class PlayerSwimState final : public PlayerBaseState
    {
        enum class Motion
        {
            Stay,
            Swim,
            Run,
            Float,
            Dive,
            Door,
        };

    private:
        Motion m_motion = Motion::Stay;
    private:
        void onLanding()override;

        void onCollisionStay(const PenetrateFloorActor& col) override;
        void onCollisionStay(const LadderActor& col) override;
        void onCollisionStay(const DoorActor& col) override;

        void start() override;
        void update(double dt)override;
        void onDraw(const PlayerVM& view)const override;
    };
}