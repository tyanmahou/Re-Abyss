#pragma once

namespace abyss::ui
{
    class IUpdate
    {
    public:
        virtual ~IUpdate() = default;
        virtual void onUpdate() = 0;
    };
}