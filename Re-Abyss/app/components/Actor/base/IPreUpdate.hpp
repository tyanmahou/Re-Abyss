#pragma once

namespace abyss::Actor
{
    class IPreUpdate
    {
    public:
        virtual ~IPreUpdate() = default;
        virtual void onPreUpdate() = 0;
    };
}