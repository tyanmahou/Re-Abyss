#pragma once
#include <abyss/utils/DebugMenu/IInputController.hpp>

namespace abyss::DebugMenu
{
    class DefaultController : public IInputController
    {
    public:
        bool up() const override;
        bool down() const override;
        bool decide() const override;
        bool back() const override;
    };
}
