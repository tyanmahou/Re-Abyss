#pragma once
#include <memory>
namespace abyss::Cycle::Title::Cursor
{
    class CursorVM;

    class Cursor
    {
    public:
        enum class Mode
        {
            GameStart,
            Exit,

            Min = GameStart,
            Max = Exit,
            Term
        };
    private:
        Mode m_mode = Mode::GameStart;

        std::unique_ptr<CursorVM> m_view;
    public:
        Cursor();
        ~Cursor();

        void update();

        void draw()const;
    };
}