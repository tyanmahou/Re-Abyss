#pragma once
namespace abyss::Actor
{
    class IUpdate
    {
    public:
        virtual ~IUpdate() = default;
        virtual void onUpdate(double dt) = 0;
    };
}