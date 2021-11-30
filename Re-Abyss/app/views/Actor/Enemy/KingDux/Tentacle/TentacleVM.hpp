#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    class TentacleVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_rotate = 0;
        bool m_isDamaging = false;
        double m_time = 0;
    public:
        TentacleVM();

        TentacleVM& setTime(double time);
        TentacleVM& setPos(const s3d::Vec2& pos);
        TentacleVM& setRotate(double rotate);
        TentacleVM& setIsDamaging(bool isDamaging);
        void draw() const;
    };
}