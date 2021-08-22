#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class TalkState final : public BaseState
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
    public:
        TalkState();
    private:
        void onLanding()override;

        void start()override;
        void update()override;
        void lastUpdate()override;
        void onDraw(const PlayerVM& view)const override;
    private:
        Motion m_motion = Motion::Stay;
    };
}