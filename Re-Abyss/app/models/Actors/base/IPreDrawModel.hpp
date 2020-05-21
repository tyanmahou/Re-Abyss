#pragma once
namespace abyss
{
    class IPreDrawModel
    {
    public:
        virtual ~IPreDrawModel() = default;
        virtual void onPreDraw(double dt) = 0;
    };
}