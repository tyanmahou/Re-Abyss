#pragma once
#if ABYSS_DEVELOP
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Layout/Window/Window.hpp>

namespace abyss::Devs::Project
{
    class TaskBoard
    {
    public:
        TaskBoard(Project* project);

        void draw() const;
    private:
        Project* m_project;
        std::unique_ptr<Layout::Window::Window> m_window;
    };
}
#endif
