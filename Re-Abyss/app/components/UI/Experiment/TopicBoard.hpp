#pragma once
#if ABYSS_DEVELOP
#include <abyss/utils/Layout/Window/Window.hpp>

namespace abyss::UI::Experiment
{
    class TopicBoard
    {
    public:
        TopicBoard();

    private:
        std::unique_ptr<Layout::Window::Window> m_window;
    };
}
#endif
