#include "XtoVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

#include <abyss/commons/ColorDef.hpp>

namespace abyss::Actor::Ooparts::Xto
{
    XtoVM::XtoVM():
        m_texture(Resource::Assets::Main()->loadTexture(U"actors/Ooparts/Xto/xto.png"))
    {}

    void XtoVM::drawCharacter(const s3d::Vec2& pos, const s3d::ColorF& color) const
    {
        bool isRight = m_forward == Forward::Right;
        int32 page = static_cast<int32>(Periodic::Square0_1(1s, m_time)) % 2;
        m_texture({ 0, 20 * page }, { 20, 20 }).mirrored(isRight).drawAt(pos, color);
    }
}
