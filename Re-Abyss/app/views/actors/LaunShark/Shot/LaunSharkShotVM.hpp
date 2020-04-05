#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss
{
    class LaunSharkShotVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
        double m_rotate;

        bool m_isDamaging = false;
    public:
        LaunSharkShotVM();
        LaunSharkShotVM& setPos(const s3d::Vec2& pos);
        LaunSharkShotVM& setRotate(double rotate);

        LaunSharkShotVM& setIsDamaging(bool isDamaging);

        void draw(double t) const;
        void drawWait() const;
        void drawFiringed() const;
    };
}