#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Player
{
    class IGimmickReactor
    {
    public:
        virtual ~IGimmickReactor() = default;

        virtual void onGimmickReact(ActorObj* player) = 0;
    };
}