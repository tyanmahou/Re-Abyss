#include <abyss/views/Actor/Gimmick/ShutterWall/ShutterWallVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Gimmick/ShutterWall/Param.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    ShutterWallVM::ShutterWallVM():
        m_texture(Resource::Assets::Main()->load(U"Actor/Gimmick/ShutterWall/ShutterWall.json"))
    {
    }
    void ShutterWallVM::draw() const
    {
        const Vec2& baseSize = Param::BaseSize;
        m_texture(U"Wall")(0, 0, baseSize.x, baseSize.y * m_shutterRate)
            .draw(m_pos - baseSize / 2, m_colorMul);

    }
}
