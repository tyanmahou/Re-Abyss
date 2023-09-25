#include <abyss/views/UI/DevPortal/TaskBoard/TaskBoardView.hpp>
#if ABYSS_DEVELOP
#include <abyss/modules/Devs/Project/Project.hpp>
#include <abyss/commons/FontName.hpp>

namespace abyss::UI::DevPortal::TaskBoard
{
    using namespace Devs::Project;

    TaskBoardView& TaskBoardView::setProject(Devs::Project::Project* project)
    {
        // In Progressタスク
        const std::tuple<TaskStatus, ColorF> statuInfos[] = {
            {TaskStatus::InProgress, Color(201, 255, 80)},
            {TaskStatus::Todo, Color(168, 255, 243)},
        };
        for (const auto& [statusName, statusColor] : statuInfos) {
            for (auto&& issue : project->issues(statusName)) {
                m_list.push_back({
                    .title = issue.title,
                    .onClick = [project, url = issue.url]() {
                        project->open(url);
                    },
                    .backGroundColor = statusColor,
                });
            }
        }
        return *this;
    }

    void TaskBoardView::draw() const
    {
        m_list.draw();
    }
}
#endif
