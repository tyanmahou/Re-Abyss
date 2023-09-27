#include <abyss/views/UI/DevPortal/TaskBoard/TaskBoardView.hpp>
#if ABYSS_DEVELOP
#include <abyss/modules/Devs/Project/Project.hpp>
#include <abyss/commons/FontName.hpp>

namespace abyss::UI::DevPortal::TaskBoard
{
    using namespace Devs::Project;

    Coro::Generator<List::SimpleVerticalList::Record> TaskBoardView::getList() const
    {
        // In Progressタスク
        const std::tuple<TaskStatus, ColorF> statuInfos[] = {
            {TaskStatus::InProgress, Color(201, 255, 80)},
            {TaskStatus::Todo, Color(168, 255, 243)},
        };
        for (const auto& [statusName, statusColor] : statuInfos) {
            for (auto&& issue : m_pProject->issues(statusName)) {
                co_yield {
                    .title = issue.title,
                    .onClick = [this, url = issue.url]() {
                        m_pProject->open(url);
                    },
                    .backGroundColor = statusColor,
                };
            }
        }
    }

    TaskBoardView::TaskBoardView()
    {
        m_list.setList(this);
    }

    TaskBoardView& TaskBoardView::setProject(Devs::Project::Project* project)
    {
        m_pProject = project;
        return *this;
    }

    void TaskBoardView::draw() const
    {
        m_list.draw();
    }
}
#endif
