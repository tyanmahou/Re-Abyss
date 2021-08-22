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
        TalkState(const Ref<ILocator>& pTargetLocator = nullptr);
    private:
        void onLanding()override;

        void start()override;
        void end()override;
        void update()override;
        void lastUpdate()override;
        void onDraw(const PlayerVM& view)const override;
    private:
        Ref<ILocator> m_pTargetLocator;
        Motion m_motion = Motion::Stay;
    };
}