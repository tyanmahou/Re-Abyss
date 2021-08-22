#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class TalkState final : public BaseState
    {
    public:
        TalkState();
    private:
        void start()override;
        void update()override;
        void onDraw(const PlayerVM& view)const override;
    };
}