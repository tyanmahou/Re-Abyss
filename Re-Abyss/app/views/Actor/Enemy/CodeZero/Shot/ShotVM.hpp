#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class ShotVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_scale;
        double m_time = 0;

        bool m_isCharge = false;
    public:
        ShotVM();

        ShotVM& setTime(double time);
        ShotVM& setPos(const s3d::Vec2& pos);
        ShotVM& setScale(double scale);
        ShotVM& setIsCharge(bool isCharge)
        {
            m_isCharge = isCharge;
            return *this;
        }
        void draw() const;
    };
}