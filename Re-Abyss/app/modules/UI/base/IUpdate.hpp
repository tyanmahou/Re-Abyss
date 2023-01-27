#pragma once

namespace abyss::UI
{
    class IUpdate
    {
    public:
        virtual ~IUpdate() = default;
        virtual void onUpdate() = 0;
    };
}