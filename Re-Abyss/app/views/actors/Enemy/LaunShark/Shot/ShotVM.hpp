#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Actor::LaunShark::Shot
{
    class ShotVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_rotate;

        bool m_isDamaging = false;
        double m_time = 0;
    public:
        ShotVM();
        ShotVM& setTime(double m_time);

        ShotVM& setPos(const s3d::Vec2& pos);
        ShotVM& setRotate(double rotate);

        ShotVM& setIsDamaging(bool isDamaging);

        void draw(double t) const;
        void drawWait() const;
        void drawFiringed() const;
    };
}