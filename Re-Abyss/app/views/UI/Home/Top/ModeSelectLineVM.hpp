#pragma once
#include <Siv3D/Line.hpp>

namespace abyss::UI::Home::Top
{
    class ModeSelectLineVM
    {
    public:
        ModeSelectLineVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        ModeSelectLineVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        ModeSelectLineVM& setScale(double scale)
        {
            m_scale = scale;
            return *this;
        }
        ModeSelectLineVM& setLocked(bool isLocked)
        {
            m_isLocked = isLocked;
            return *this;
        }
        ModeSelectLineVM& setLine(const s3d::Line& line0, const s3d::Line& line1)
        {
            m_line0 = line0;
            m_line1 = line1;
            return *this;
        }
        ModeSelectLineVM& setText(const s3d::String& text)
        {
            m_text = text;
            return *this;
        }
        ModeSelectLineVM& setTextOffset(const s3d::Vec2& offset)
        {
            m_textOffset = offset;
            return *this;
        }
        void draw() const;
    private:
        s3d::Vec2 m_pos{};
        double m_time = 0;
        double m_scale = 1.0;
        s3d::Line m_line0, m_line1;

        s3d::String m_text;
        s3d::Vec2 m_textOffset;
        bool m_isLocked = false;
    };
}
