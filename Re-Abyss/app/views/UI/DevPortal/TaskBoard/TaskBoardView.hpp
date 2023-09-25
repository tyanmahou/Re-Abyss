#pragma once
#if ABYSS_DEVELOP
#include <abyss/commons/Fwd.hpp>
#include <abyss/views/util/List/SimpleVerticalList.hpp>

namespace abyss::UI::DevPortal::TaskBoard
{
    class TaskBoardView
    {
    public:
        TaskBoardView& setScreen(const RectF& screen)
        {
            m_list.setScreen(screen);
            return *this;
        }
        TaskBoardView& setProject(Devs::Project::Project* project);

        void draw() const;
    private:
        List::SimpleVerticalList m_list;
    };
}
#endif
