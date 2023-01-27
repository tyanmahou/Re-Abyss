#pragma once

namespace abyss::Effect
{
    class IUpdate
    {
    public:
        virtual ~IUpdate() = default;

        virtual void onUpdate() = 0;
    };
}