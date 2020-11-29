#pragma once
namespace abyss::Actor
{
    class IPreDraw
    {
    public:
        virtual ~IPreDraw() = default;
        virtual void onPreDraw() = 0;
    };
}