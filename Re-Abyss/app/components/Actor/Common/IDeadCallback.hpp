#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor
{
    class IDeadCallback
    {
    public:
        virtual ~IDeadCallback() = default;
        virtual void onDead() = 0;
    };
}