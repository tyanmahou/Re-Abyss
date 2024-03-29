#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
    class EyeVM
    {
    public:
        EyeVM();
        EyeVM& setPos(const s3d::Vec2& pos);
        EyeVM& setScale(double scale);
        EyeVM& setColorMul(const s3d::ColorF color);
        EyeVM& setColorAdd(const s3d::ColorF color);
        void draw() const;
    private:
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_scale = 1.0;
        s3d::ColorF m_colorMul;
        s3d::ColorF m_colorAdd;
    };
}