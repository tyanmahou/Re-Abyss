#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/Devs/GitHub/GitHub.hpp>
#include <abyss/utils/Layout/Window/Window.hpp>

namespace abyss::Devs::GitHub
{
    class TaskBoard
    {
    public:
        TaskBoard();

        void draw() const;
    private:
        Devs::GitHub::GitHub m_gitHub;
        Font m_font{ 16, Typeface::Regular };
        std::unique_ptr<Layout::Window::Window> m_window;
    };
}
#endif
