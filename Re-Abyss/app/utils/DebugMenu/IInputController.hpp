#pragma once

namespace abyss::DebugMenu
{
    class IInputController
    {
    public:
        virtual ~IInputController() = default;

        virtual bool up() const = 0;
        virtual bool down() const = 0;

        virtual bool decide() const = 0;
        virtual bool back() const = 0;
    };
}
