#include <abyss/modules/Devs/GitHub/TaskBoard.hpp>
#if ABYSS_DEVELOP
#include <abyss/commons/Constants.hpp>

namespace abyss::Devs::GitHub
{
    TaskBoard::TaskBoard()
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
        m_window->draw([&](const RectF& sceneScreen) {
            // In Progressタスク
            const std::tuple<String, ColorF> statuInfos[] = {
                {U"In Progress", Color(201, 255, 80)},
                {U"Todo", Color(168, 255, 243)},
            };
            const Vec2 columnSize{ sceneScreen.w, m_font.height(16) };
            size_t index = 0;
            for (const auto& [statusName, statusColor] : statuInfos) {
            
                for (auto&& issue : m_gitHub.getIssues(statusName)) {
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
                    m_font(issue.title).draw(column, Palette::Black);
            
                    if (column.leftClicked()) {
                        m_gitHub.open(issue.url);
                    }
                    ++index;
                }
            }
        });
    }
}
#endif
