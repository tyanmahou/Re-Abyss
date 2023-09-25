#include <abyss/components/UI/DevPortal/TaskBoard/TaskBoard.hpp>

#if ABYSS_DEVELOP
#include <abyss/commons/Constants.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/views/UI/DevPortal/TaskBoard/TaskBoardView.hpp>

namespace abyss::UI::DevPortal::TaskBoard
{
    TaskBoard::TaskBoard(UIObj* pUi):
        m_pUi(pUi),
        m_project(pUi->getModule<Project>()),
        m_view(std::make_unique<TaskBoardView>())
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
    TaskBoard::~TaskBoard()
    {
    }
    void TaskBoard::onStart()
    {
        m_view->setProject(m_project);
    }
    void TaskBoard::onDraw() const
    {
        m_window->draw([&](const RectF& sceneScreen) {
            m_view
                ->setScreen(sceneScreen)
                .draw();
        });
    }
}
#endif
