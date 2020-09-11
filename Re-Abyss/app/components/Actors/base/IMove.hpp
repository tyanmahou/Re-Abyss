#pragma once
namespace abyss::Actor
{
    class IMove
    {
    public:
        virtual ~IMove() = default;
        virtual void onMove(double dt) = 0;
    };
}