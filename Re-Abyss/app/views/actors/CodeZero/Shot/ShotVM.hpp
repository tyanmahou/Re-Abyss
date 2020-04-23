#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
namespace abyss::CodeZero::Shot
{
    class ShotVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_scale;
    public:
        ShotVM();

        ShotVM& setPos(const s3d::Vec2& pos);
        ShotVM& setScale(double scale);

        void draw() const;
        void drawCharge()const;
    };
}