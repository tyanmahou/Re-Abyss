#pragma once
#if ABYSS_DEVELOP
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Layout/Window/Window.hpp>

namespace abyss::Devs::GitHub
{
    class TaskBoard
    {
    public:
        TaskBoard(GitHub* gitHub);

        void draw() const;
    private:
        Devs::GitHub::GitHub* m_gitHub;
        std::unique_ptr<Layout::Window::Window> m_window;
    };
}
#endif
