#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor
{
    class IStateCallback
    {
    public:
        virtual ~IStateCallback() = default;
        virtual void onStateStart() = 0;
    };
}