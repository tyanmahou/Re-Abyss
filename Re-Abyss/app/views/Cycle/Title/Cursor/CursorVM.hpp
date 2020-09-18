#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Cycle::Title::Cursor
{
    /// <summary>
    /// カーソル
    /// </summary>
    class CursorVM
    {
    private:
        TexturePacker m_texture;
        s3d::Vec2 m_pos;
    public:
        CursorVM();

        CursorVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }

        void draw() const;
    };
}