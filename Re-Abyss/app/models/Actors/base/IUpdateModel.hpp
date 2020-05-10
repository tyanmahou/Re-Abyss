#pragma once
namespace abyss
{
    class IUpdateModel
    {
    public:
        virtual ~IUpdateModel() = default;
        virtual void onUpdate(double dt) = 0;
    };
}