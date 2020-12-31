#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Player
{
    class IGimmickReacter
    {
    public:
        virtual ~IGimmickReacter() = default;

        virtual void onGimmickReact(IActor* player) = 0;
    };
}