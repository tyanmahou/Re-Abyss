#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Actor::Enemy::KingDux::Foot
{
    class FootVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_rotate = 0;
        bool m_isDamaging = false;
        bool m_isFlip = false;
        double m_time = 0;
    public:
        FootVM();
        FootVM& setTime(double time);
        FootVM& setPos(const s3d::Vec2& pos);
        FootVM& setRotate(double rotate);

        FootVM& setIsDamaging(bool isDamaging);
        FootVM& setIsFlip(bool isFlip);
        void draw() const;
    };
}
