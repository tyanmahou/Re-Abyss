#pragma once

namespace abyss::Event
{
    class ILastUpdate
    {
    public:
        virtual ~ILastUpdate() = default;

        virtual void onLastUpdate() = 0;
    };
}