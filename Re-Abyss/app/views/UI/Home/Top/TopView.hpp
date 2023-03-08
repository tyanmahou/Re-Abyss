#pragma once

namespace abyss::UI::Home::Top
{
    class ModeIconVM;

    class TopView
    {
        enum {
            IconSeek,
            IconGuild,
            IconFactory,
            IconCollect,
            IconMemory,
            IconOption,
            IconSize,
        };
    public:
        TopView();
        ~TopView();
        void draw() const;
    private:
        std::unique_ptr<ModeIconVM[]> m_icons;
        s3d::Font m_font;
    };
}
