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
        TopView& setInAnimeRate(double rate)
        {
            m_inAnimeRate = rate;
            return *this;
        }
        TopView& setMode(Mode mode)
        {
            m_mode = mode;
            return *this;
        }
        TopView& setLock(Mode mode, bool isLocked)
        {
            m_isLocked[static_cast<size_t>(mode)] = isLocked;
            return *this;
        }
        void draw() const;
    private:
        double m_time = 0;
        double m_inAnimeRate = 0;
        Mode m_mode;
        std::unique_ptr<ModeIconVM[]> m_icons;
        std::unique_ptr<ModeSelectLineVM> m_selectLine;

        std::array<bool, IconSize> m_isLocked;
    };
}
