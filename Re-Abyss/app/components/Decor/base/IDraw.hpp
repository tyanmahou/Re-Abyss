#pragma once

namespace abyss::decor
{
    class IDraw
    {
    public:
        virtual ~IDraw() = default;
        virtual void onDraw()const = 0;
    };
}