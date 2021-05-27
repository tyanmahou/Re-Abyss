#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Item
{
    class IItemReactor
    {
    public:
        virtual ~IItemReactor() = default;

        virtual void onGained(ActorObj* player) = 0;
    };
}