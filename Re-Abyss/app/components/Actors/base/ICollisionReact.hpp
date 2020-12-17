#pragma once
#include <abyss/commons/Fwd.hpp>
namespace abyss::Actor
{
    class ICollisionReact
    {
    public:
        virtual ~ICollisionReact() = default;
        virtual void onCollisionReact() = 0;
    };
}