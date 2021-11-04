#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::UI::Message
{
    class CursorVM
    {
        s3d::Texture m_texture;
        s3d::Vec2 m_pos;
        bool m_isVertical = true;
    public:
        CursorVM();
        CursorVM& setPos(const s3d::Vec2& pos);
        CursorVM& setVertical(bool isVertical)
        {
            m_isVertical = isVertical;
            return *this;
        }

        void draw() const;
    };
}