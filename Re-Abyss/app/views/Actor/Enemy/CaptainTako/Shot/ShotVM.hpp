#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/values/Forward.hpp>

namespace abyss::Actor::Enemy::CaptainTako::Shot
{
    class ShotVM
    {
        TexturePacker m_texture;
        Forward m_forward;
        s3d::Vec2 m_pos;

        double m_time = 0;
    public:
        ShotVM();
        ShotVM& setTime(double time);
        ShotVM& setForward(const Forward& forward);
        ShotVM& setPos(const s3d::Vec2& pos);

        void draw() const;
    };
}