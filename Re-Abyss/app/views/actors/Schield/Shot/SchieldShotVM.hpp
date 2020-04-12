#pragma once

#include <Siv3D/Vector2D.hpp>

#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss
{
    class SchieldShotVM
    {
        TexturePacker m_texture;

        s3d::Vec2 m_pos;
    public:
        SchieldShotVM();
        SchieldShotVM& setPos(const s3d::Vec2& pos);

        void draw() const;
    };
}