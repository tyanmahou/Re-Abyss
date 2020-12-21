#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>

namespace abyss::Actor
{
    class ICollider
    {
    public:
        virtual ~ICollider() = default;
        virtual CShape getCollider() const = 0;
    };
}