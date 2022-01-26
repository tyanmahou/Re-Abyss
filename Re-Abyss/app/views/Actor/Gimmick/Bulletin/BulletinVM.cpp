#include <abyss/views/Actor/Gimmick/Bulletin/BulletinVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Gimmick::Bulletin
{
    BulletinVM::BulletinVM():
        m_texture(Resource::Assets::Main()->load(U"actors/Gimmick/Bulletin/bulletin.png"))
    {}
    BulletinVM& BulletinVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    void BulletinVM::draw() const
    {
        m_texture.drawAt(m_pos);
    }
}
