#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/utils/Look/Look.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
    class HeadVM
    {
    public:
        HeadVM();
        HeadVM& setTime(double time);
        HeadVM& setPos(const s3d::Vec2& pos);
        HeadVM& setLook(const Look& look);
        HeadVM& setColorMul(const s3d::ColorF color);
        HeadVM& setColorAdd(const s3d::ColorF color);
        void draw() const;
    private:
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        Look m_look;
        double m_time = 0;

        s3d::ColorF m_colorMul;
        s3d::ColorF m_colorAdd;
    };
}
