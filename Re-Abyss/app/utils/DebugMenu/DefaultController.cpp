#include <abyss/utils/DebugMenu/DefaultController.hpp>
#include <Siv3D/Keyboard.hpp>

namespace abyss::DebugMenu
{
    bool DefaultController::up() const
    {
        return s3d::KeyUp.down();
    }
    bool DefaultController::down() const
    {
        return s3d::KeyDown.down();
    }
    bool DefaultController::decide() const
    {
        return s3d::KeyZ.down();
    }
    bool DefaultController::back() const
    {
        return s3d::KeyX.down();
    }
}
