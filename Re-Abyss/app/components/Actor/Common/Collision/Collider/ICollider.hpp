#pragma once
#include <abyss/types/CShape.hpp>

namespace abyss::Actor::Collision
{
    class ICollider
    {
    public:
        virtual ~ICollider() = default;
        virtual void onStart() {}
        virtual CShape getCollider() const = 0;
    };
}