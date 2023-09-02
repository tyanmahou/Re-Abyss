#pragma once
#if ABYSS_DEVELOP
#include <abyss/commons/Fwd.hpp>

namespace abyss::UI::DevPortal::TaskBoard
{
    class TaskBoardView
    {
    public:
        TaskBoardView& setScreen(const RectF& screen)
        {
            m_screen = screen;
            return *this;
        }
        void draw(Devs::Project::Project* project) const;
    private:
        RectF m_screen;
    };
}
#endif
