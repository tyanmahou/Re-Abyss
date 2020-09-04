#pragma once

#include <Siv3D/Vector2D.hpp>

#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Actor::Enemy::Schield::Shot
{
    class ShotVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_time = 0;
    public:
        ShotVM();
        ShotVM& setTime(double time);
        ShotVM& setPos(const s3d::Vec2& pos);

        void draw() const;
    };
}