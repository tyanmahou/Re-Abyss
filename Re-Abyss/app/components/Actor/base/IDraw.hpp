#pragma once
namespace abyss::Actor
{
    class IDraw
    {
    public:
        virtual ~IDraw() = default;
        virtual void onDraw()const = 0;
    };
}