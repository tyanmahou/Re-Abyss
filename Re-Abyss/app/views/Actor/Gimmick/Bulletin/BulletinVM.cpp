#include "BulletinVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Gimmick::Bulletin
{
    BulletinVM::BulletinVM():
        m_texture(Resource::Assets::Main()->loadTexture(U"actors/Gimmick/Bulletin/bulletin.png"))
    {}
    void BulletinVM::draw() const
    {
        m_texture.drawAt(m_pos);
    }
}
