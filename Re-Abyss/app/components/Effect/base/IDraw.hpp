#pragma once

namespace abyss::Effect
{
    class IDraw
    {
    public:
        virtual ~IDraw() = default;

        virtual bool onDraw(double time) = 0;
    };
}