#include <abyss/views/Actor/Ooparts/Nyan/NyanVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Ooparts::Nyan
{
    NyanVM::NyanVM():
        m_texture(Resource::Assets::Main()->load(U"Actor/Ooparts/Nyan/Nyan.png"))
    {}
    void NyanVM::draw(const s3d::ColorF & color) const
    {
        bool isRight = m_forward == Forward::Right;
        int32 page = static_cast<int32>(Periodic::Square0_1(1s, m_time)) % 2;
        m_texture({ 0, 20 * page }, { 20, 20 }).mirrored(isRight).drawAt(m_pos, color);
    }
    s3d::TextureRegion NyanVM::icon() const
    {
        return m_texture({ 0, 0 }, {20, 20});
    }
}
