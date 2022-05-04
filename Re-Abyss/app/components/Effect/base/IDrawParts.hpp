#pragma once

namespace abyss::Effect
{
    class IDrawParts
    {
    public:
        virtual ~IDrawParts() = default;

        virtual bool onDraw(double time) = 0;
    };
}