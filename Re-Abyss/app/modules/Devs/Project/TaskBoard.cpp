#if ABYSS_DEVELOP
#include <abyss/modules/Devs/Project/TaskBoard.hpp>
#include <abyss/modules/Devs/Project/Project.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/FontName.hpp>

namespace abyss::Devs::Project
{
    TaskBoard::TaskBoard(Project* project) :
        m_project(project)
    {
        auto windowContext =
            Layout::Window::WindowContext{ Vec2{Constants::AppResolutionF.x - 400 - 10 , 10}, Vec2{400, 600} }
            .setBackGroundColor(ColorF(0.5, 0.5))
            .setFrameColor(s3d::Palette::White)
            .setScrollBarColor(ColorF(0, 0.5))
            .setScrollGripColor(ColorF(0.9))
            .setCanResize(true)
            .setIsResizeClampSceneSize(false)
            ;
        m_window = std::make_unique<Layout::Window::Window>(windowContext);
    }
    void TaskBoard::draw() const
    {
        auto font = FontAsset(FontName::DebugLog);

        m_window->draw([&](const RectF& sceneScreen) {
            // In Progressタスク
            const std::tuple<TaskStatus, ColorF> statuInfos[] = {
                {TaskStatus::InProgress, Color(201, 255, 80)},
                {TaskStatus::Todo, Color(168, 255, 243)},
            };
            const Vec2 columnSize{ sceneScreen.w, font.height(16) };
            size_t index = 0;
            for (const auto& [statusName, statusColor] : statuInfos) {
            
                for (auto&& issue : m_project->issues(statusName)) {
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
                        m_project->open(issue.url);
                    }
                    ++index;
                }
            }
        });
    }
}
#endif
