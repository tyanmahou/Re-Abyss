#include <abyss/views/Actor/Gimmick/ShutterWall/ShutterWallVM.hpp>
#include <abyss/params/Actor/Gimmick/ShutterWall/Param.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    ShutterWallVM::ShutterWallVM()
    {
    }
    void ShutterWallVM::draw() const
    {
        const Vec2& baseSize = Param::BaseSize;
        RectF(
            m_pos - baseSize / 2,
            baseSize.x,
            baseSize.y * m_shutterRate
        ).draw(m_colorMul);
    }
}
