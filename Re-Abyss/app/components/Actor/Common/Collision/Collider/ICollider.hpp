#pragma once
#include <abyss/types/CShape.hpp>
#include <abyss/components/base/Executer.hpp>

namespace abyss::Actor::Collision
{
    class ICollider
    {
    public:
        virtual ~ICollider() = default;
        virtual void setup([[maybe_unused]] Executer executer) {}
        virtual void onStart() {}
        virtual CShape getCollider() const = 0;
    };
}