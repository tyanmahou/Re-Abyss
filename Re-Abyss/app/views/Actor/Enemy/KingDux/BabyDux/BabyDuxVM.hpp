#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    class BabyDuxVM
    {
        s3d::Texture m_texture;

        s3d::Vec2 m_pos;
        bool m_isDamaging = false;
        double m_time = 0;
    public:
        BabyDuxVM();
        BabyDuxVM& setTime(double time);
        BabyDuxVM& setPos(const s3d::Vec2& pos);

        BabyDuxVM& setIsDamaging(bool isDamaging);
        void draw() const;
    };
}
