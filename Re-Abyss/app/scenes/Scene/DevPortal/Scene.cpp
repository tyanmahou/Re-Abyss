#include <abyss/scenes/Scene/DevPortal/Scene.hpp>
#include <abyss/debugs/Debug.hpp>
#include <abyss/modules/Devs/GitHub/GitHub.hpp>
#include <Siv3D.hpp>

#include <abyss/utils/Layout/Window/Window.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Constants.hpp>
#if ABYSS_DEVELOP

namespace abyss::Scene::DevPortal
{
    class TaskBoard
    {
    public:
        TaskBoard()
        {
            auto windowContext =
                Layout::Window::WindowContext{ Vec2{Constants::AppResolutionF.x -400-10 , 10}, Vec2{400, 600} }
                .setBackGroundColor(ColorF(0.5, 0.5))
                .setFrameColor(s3d::Palette::White)
                .setScrollBarColor(ColorF(0, 0.5))
                .setScrollGripColor(ColorF(0.9))
                .setCanResize(true)
                .setIsResizeClampSceneSize(false)
                ;
            m_window = std::make_unique<Layout::Window::Window>(windowContext);

        }

        void draw() const
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
    private:
        Devs::GitHub::GitHub m_gitHub;
        Font m_font{ 16, Typeface::Regular };
        std::unique_ptr<Layout::Window::Window> m_window;
    };
    class Scene::Impl
    {
    public:
        Impl(const InitData& init) :
            m_data(init._s)
        {
        }

        void update()
        {
            if (KeyEnter.down()) {
                m_data->isRequestedSceneEnd = true;
            }
        }
        void draw()
        {
            s3d::Scene::Rect().draw(ColorDef::DefaultFadeColor);
            m_font(U"[DevPortal] Push Enter Start").draw();
            m_task.draw();
        }
    private:
        std::shared_ptr<Data_t> m_data;
        Font m_font{ 20 };

        TaskBoard m_task;
    };
    Scene::Scene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
    }
    Scene::~Scene()
    {}
    void Scene::onSceneUpdate()
    {
        m_pImpl->update();
    }

    void Scene::onSceneDraw() const
    {
        m_pImpl->draw();
    }
}
#endif
