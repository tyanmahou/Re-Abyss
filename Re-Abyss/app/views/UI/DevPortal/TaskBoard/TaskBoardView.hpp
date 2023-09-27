#pragma once
#if ABYSS_DEVELOP
#include <abyss/commons/Fwd.hpp>
#include <abyss/views/util/List/SimpleVerticalList.hpp>

namespace abyss::UI::DevPortal::TaskBoard
{
    class TaskBoardView : public List::SimpleVerticalList::IContents
    {
    public:
        TaskBoardView();

        TaskBoardView& setScreen(const RectF& screen)
        {
            m_list.setScreen(screen);
            return *this;
        }
        TaskBoardView& setProject(Devs::Project::Project* project);

        void draw() const;
    public:
        Coro::Generator<List::SimpleVerticalList::Record> getList() const override;
    private:
        Devs::Project::Project* m_pProject;
        List::SimpleVerticalList m_list;
    };
}
#endif
