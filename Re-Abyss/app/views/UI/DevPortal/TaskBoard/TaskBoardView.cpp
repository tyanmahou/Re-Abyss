#include <abyss/views/UI/DevPortal/TaskBoard/TaskBoardView.hpp>
#if ABYSS_DEVELOP
#include <abyss/modules/Devs/Project/Project.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/FontName.hpp>

namespace abyss::UI::DevPortal::TaskBoard
{
    using namespace Devs::Project;

    void TaskBoardView::draw(Project* project) const
    {
        auto font = FontAsset(FontName::DebugLog);

        // In Progressタスク
        const std::tuple<TaskStatus, ColorF> statuInfos[] = {
            {TaskStatus::InProgress, Color(201, 255, 80)},
            {TaskStatus::Todo, Color(168, 255, 243)},
        };
        const Vec2 columnSize{ m_screen.w, font.height(16) };
        size_t index = 0;
        for (const auto& [statusName, statusColor] : statuInfos) {

            for (auto&& issue : project->issues(statusName)) {
                RectF column(0, columnSize.y * index, columnSize);
                ColorF color(statusColor);
                if (column.mouseOver()) {
                    HSV hsv(color);
                    hsv.s += 0.1;
                    hsv.v -= 0.1;
                    color = hsv;
                    s3d::Cursor::RequestStyle(CursorStyle::Hand);
                }
                column.draw(color.setA(0.9));
                font(issue.title).draw(column, Palette::Black);

                if (column.leftReleased()) {
                    project->open(issue.url);
                }
                ++index;
            }
        }
    }
}
#endif
