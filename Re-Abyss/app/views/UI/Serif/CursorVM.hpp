#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::ui::Serif
{
    class CursorVM
    {
        s3d::Texture m_texture;
        s3d::Vec2 m_pos;
    public:
        CursorVM();
        CursorVM& setPos(const s3d::Vec2& pos);

        void draw() const;
    };
}