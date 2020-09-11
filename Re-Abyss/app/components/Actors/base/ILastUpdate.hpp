#pragma once
namespace abyss::Actor
{
    class ILastUpdate
    {
    public:
        virtual ~ILastUpdate() = default;
        virtual void onLastUpdate() = 0;
    };
}