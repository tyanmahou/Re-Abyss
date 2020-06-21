#pragma once
namespace abyss
{
    class IPrePhysicsModel
    {
    public:
        virtual ~IPrePhysicsModel() = default;
        virtual void onPrePhysics() = 0;
    };
}