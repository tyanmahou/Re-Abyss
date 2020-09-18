#pragma once
#include <memory>
#include <array>
#include <functional>

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
        static constexpr size_t ModeTerm = static_cast<size_t>(Mode::Term);
    private:
        Mode m_mode = Mode::GameStart;

        std::array<std::function<void()>, ModeTerm> m_events;
        std::unique_ptr<CursorVM> m_view;
    public:
        Cursor();
        ~Cursor();

        void update();

        void draw()const;

        std::function<void()>& operator[](Mode mode)
        {
            return m_events[static_cast<size_t>(mode)];
        }
    };
}