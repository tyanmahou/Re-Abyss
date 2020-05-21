#include "XtoVM.hpp"
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <Siv3D.hpp>

#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss::Ooparts::Xto
{
    XtoVM::XtoVM():
        m_texture(ResourceManager::Main()->loadTexture(U"actors/Ooparts/Xto/xto.png"))
    {}

    void XtoVM::drawCharacter(const s3d::Vec2& pos, const s3d::ColorF& color, double time) const
    {
        bool isRight = m_forward == Forward::Right;
        int32 page = static_cast<int32>(Periodic::Square0_1(1s, time)) % 2;
        m_texture({ 0, 20 * page }, { 20, 20 }).mirrored(isRight).drawAt(pos);
    }
}
