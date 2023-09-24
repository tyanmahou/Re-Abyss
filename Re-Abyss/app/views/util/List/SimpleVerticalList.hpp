#pragma once

namespace abyss::UI::List
{
    class SimpleVerticalList
    {
    public:
        SimpleVerticalList& setScreen(const RectF& screen)
        {
            m_screen = screen;
            return *this;
        }
        SimpleVerticalList setFontSize(double size)
        {
            m_size = size;
            return *this;
        }
        void draw() const;
    public:
        RectF m_screen;
        double m_size;
    };
}
