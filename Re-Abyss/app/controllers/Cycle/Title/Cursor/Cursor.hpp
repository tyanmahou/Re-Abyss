#pragma once
#include <memory>
#include <array>
#include <functional>
#include <Siv3D/Timer.hpp>

namespace abyss::Cycle::Title::Cursor
{
    class Shot;
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

        s3d::Timer m_gameStartTimer;
        bool m_isGameStart = false;
        std::unique_ptr<Shot> m_shot;
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