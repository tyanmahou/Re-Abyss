#pragma once
#include <abyss/components/UI/Home/Top/Mode.hpp>

namespace abyss::UI::Home::Top
{
    class ModeIconVM;
    class ModeSelectLineVM;

    class TopView
    {
        enum {
            IconSeek,
            IconGuild,
            IconMaint,
            IconMemory,
            IconCollect,
            IconOption,
            IconSize,
        };
    public:
        TopView();
        ~TopView();
        TopView& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        TopView& setMode(Mode mode)
        {
            m_mode = mode;
            return *this;
        }
        void draw() const;
    private:
        double m_time = 0;
        Mode m_mode;
        std::unique_ptr<ModeIconVM[]> m_icons;
        std::unique_ptr<ModeSelectLineVM> m_selectLine;
    };
}
