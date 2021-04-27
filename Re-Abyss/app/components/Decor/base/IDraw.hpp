#pragma once

namespace abyss::Decor
{
    class IDraw
    {
    public:
        virtual ~IDraw() = default;
        virtual void onDraw()const = 0;
    };
}