#pragma once

namespace abyss::Effect
{
    class IDraw
    {
    public:
        virtual ~IDraw() = default;

        virtual void onDraw(double time) = 0;

        virtual bool isEnd() = 0;
    };
}