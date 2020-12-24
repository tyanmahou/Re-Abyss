#pragma once

namespace abyss::Event
{
    class IUpdate
    {
    public:
        virtual ~IUpdate() = default;

        virtual void onUpdate() = 0;
    };
}