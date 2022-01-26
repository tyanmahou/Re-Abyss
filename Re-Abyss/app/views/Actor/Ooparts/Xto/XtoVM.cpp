#include <abyss/views/Actor/Ooparts/Xto/XtoVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

#include <abyss/commons/ColorDef.hpp>

namespace abyss::Actor::Ooparts::Xto
{
    XtoVM::XtoVM():
        m_texture(Resource::Assets::Main()->load(U"actors/Ooparts/Xto/xto.png"))
    {}

    void XtoVM::draw(const s3d::ColorF & color) const
    {
        bool isRight = m_forward == Forward::Right;
        int32 page = static_cast<int32>(Periodic::Square0_1(1s, m_time)) % 2;
        m_texture({ 0, 20 * page }, { 20, 20 }).mirrored(isRight).drawAt(m_pos, color);
    }

    s3d::TextureRegion XtoVM::icon() const
    {
        return m_texture({ 0, 0 }, { 20, 20 });
    }
}
