#pragma once
namespace abyss
{
    class IDrawModel
    {
    public:
        virtual ~IDrawModel() = default;
        virtual void onDraw()const = 0;
    };
}