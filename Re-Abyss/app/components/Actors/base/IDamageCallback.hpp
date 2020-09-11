#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor
{
    class IDamageCallback
    { 
    public:
        virtual ~IDamageCallback() = default;
        virtual void onDamaged() = 0;
    };
}