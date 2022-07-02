#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    class BabyDuxVM
    {
    public:
        BabyDuxVM();
        BabyDuxVM& setTime(double time);
        BabyDuxVM& setPos(const s3d::Vec2& pos);

        BabyDuxVM& setColorMul(const s3d::ColorF color);
        void draw() const;
    private:
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_time = 0;
        s3d::ColorF m_colorMul;
    };
}
