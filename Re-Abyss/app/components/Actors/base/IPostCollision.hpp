#pragma once
#include <abyss/commons/Fwd.hpp>
namespace abyss::Actor
{
    class IPostCollision
    {
    public:
        virtual ~IPostCollision() = default;
        virtual void onPostCollision() = 0;
    };
}