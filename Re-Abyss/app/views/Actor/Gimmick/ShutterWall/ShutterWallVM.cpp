#include <abyss/views/Actor/Gimmick/ShutterWall/ShutterWallVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Gimmick/ShutterWall/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    ShutterWallVM::ShutterWallVM():
        m_texture(Resource::Assets::Main()->load(U"Actor/Gimmick/ShutterWall/ShutterWall.json"))
    {
    }
    void ShutterWallVM::draw() const
    {
        const Vec2& baseSize = Param::BaseSize;
        const Vec2 tl = m_pos - baseSize / 2;
        const double height = baseSize.y * m_shutterRate;
        m_texture(U"wall")(0, 0, baseSize.x, height)
            .draw(tl, m_colorMul);

        auto&& headTex = m_texture(U"head");
        // 下
        const double underHeadTop= Max(-2.0, height - headTex.size().y);
        headTex.flipped().draw(tl + Vec2{ -10, underHeadTop });
        // 上
        const double topHeadHeight = Round(Clamp<double>((underHeadTop + 9.0 + 7.0) / 2.0, 7.0, headTex.size().y));
        headTex(0, 0, headTex.size().x, topHeadHeight).draw(tl + Vec2{-10, 0});
    }
}
