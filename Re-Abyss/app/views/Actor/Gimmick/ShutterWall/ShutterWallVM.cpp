#include <abyss/views/Actor/Gimmick/ShutterWall/ShutterWallVM.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    ShutterWallVM::ShutterWallVM()
    {
    }
    void ShutterWallVM::draw() const
    {
        constexpr Vec2 baseSize{40, 160};
        RectF(
            m_pos - baseSize / 2,
            baseSize.x,
            baseSize.y * m_shutterRate
        ).draw();
    }
}
