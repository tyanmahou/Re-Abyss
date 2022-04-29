#pragma once
#include <abyss/modules/DrawManager/DrawLayer.hpp>
#include <abyss/modules/DrawManager/DrawOrder.hpp>

namespace abyss::Actor
{
    class IDraw
    {
    public:
        virtual ~IDraw() = default;
        virtual void onDraw()const = 0;
        virtual DrawLayer getLayer() const = 0;
        virtual double getOrder() const = 0;
    };
}