#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::Actor::Gimmick::Bulletin
{
    class BulletinVM
    {
    public:
        BulletinVM();

        BulletinVM& setPos(const s3d::Vec2& pos);

        void draw() const;
    private:
        s3d::Texture m_texture;
        s3d::Vec2 m_pos;
    };
}