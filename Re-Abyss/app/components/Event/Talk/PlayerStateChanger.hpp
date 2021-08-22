#pragma once
#include <abyss/components/Event/Common/PlayerStateCtrl.hpp>

namespace abyss::Event::Talk
{
    class PlayerStateChanger final: public IPlayerStateChanger
    {
    public:
        void onEventStart(Actor::ActorObj* player) override;
        void onEventEnd(Actor::ActorObj* player) override;
    };
}