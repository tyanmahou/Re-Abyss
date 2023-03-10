#pragma once
#include <abyss/components/UI/Home/Top/Mode.hpp>

namespace abyss::UI::Home::Top
{
    class ModeIconVM;

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
        TopView& setMode(Mode mode)
        {
            m_mode = mode;
            return *this;
        }
        void draw() const;
    private:
        Mode m_mode;
        std::unique_ptr<ModeIconVM[]> m_icons;
    };
}
