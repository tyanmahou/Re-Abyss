#pragma once

#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>

#include <abyss/types/Forward.hpp>

namespace abyss
{
    class IkalienVM
    {
        s3d::Texture m_texture;

        s3d::Vec2 m_pos;
        double m_rotate = 0.0;

        bool m_isDamaging = false;
    public:
        IkalienVM();
        IkalienVM& setPos(const s3d::Vec2& pos);
        IkalienVM& setRotate(double rotate);

        IkalienVM& setIsDamaging(bool isDamaging);

        void drawWait() const;
    };
}