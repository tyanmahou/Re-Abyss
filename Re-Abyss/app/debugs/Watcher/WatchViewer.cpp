#include <abyss/debugs/Watcher/WatchViewer.hpp>

#if ABYSS_DEBUG
#include <abyss/utils/Layout/Window/Window.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Debug;

    struct WatchInfo
    {
        s3d::String log;
    };

    class ViewerCore
    {
    public:
        ViewerCore() :
            m_font(16, Typeface::Regular)
        {
            auto windowContext = Layout::Window::WindowContext{ Vec2{Scene::Width(), 5}, Vec2{300, 150}}
                .setBackGroundColor(s3d::none)
                .setFrameColor(s3d::none)
                .setScrollBarColor(ColorF(0, 0.5))
                .setScrollGripColor(ColorF(0.9))
                //.setCanResize(false)
                .setIsResizeClampSceneSize(true)
                ;
            m_window = std::make_unique<Layout::Window::Window>(windowContext);
        }

        void draw(const s3d::Array<WatchInfo>& logs)
        {
            if (logs.isEmpty()) {
                return;
            }
            m_window->draw([&](const RectF& sceneScreen) {
                s3d::ScopedRenderStates2D sampler(s3d::SamplerState::ClampLinear);

                // ウィンドウ幅
                double width = 0;
                for (const auto& log : logs) {
                    width = s3d::Max(width, m_font(log.log).region().w);
                }
                constexpr double margin = 5.0;
                width += margin + 30;

                Vec2 pos{ 0, 0 };
                for (const auto& log : logs) {
                    auto region = m_font(log.log).region();
                    region.w = width;

                    auto area = RectF(pos, region.size);
                    if (area.y <= sceneScreen.y + sceneScreen.h && area.y + area.h >= sceneScreen.y) {
                        // 画面外の描画はしない
                        auto color = ColorF(0.0, 0.2);
                        area.draw(color);

                        auto logPos = pos;
                        logPos.x += margin;
                        m_font(log.log).draw(logPos);
                    }
                    pos.y += region.h;
                }

                bool isScrollButtom = m_window->isScrollBottom();
                {
                    auto sizePrev = m_size;
                    m_size = Vec2{ s3d::Min<double>(width, s3d::Scene::Width()), s3d::Min<double>(pos.y, s3d::Scene::Height()) };

                    Vec2 nextSize = sceneScreen.size;
                    if (sceneScreen.size.x >= sizePrev.x) {
                        nextSize.x = m_size.x;
                    }
                    m_window->setSize(nextSize);
                }
                m_window->setSceneSize({ width, s3d::Max(pos.y, 150.0) });
                if (isScrollButtom) {
                    m_window->setScenePosToBottom();
                }
                // 座標調整
                {
                    auto posPrev = m_pos;
                    m_pos = Vec2{ Scene::Width() - width - 5, 5 };

                    const Vec2 globalPos = m_window->region().pos;
                    Vec2 nextPos = globalPos;
                    if (globalPos.x >= posPrev.x) {
                        nextPos.x = m_pos.x;
                    }
                    if (globalPos.y <= posPrev.y) {
                        nextPos.y = m_pos.y;
                    }
                    m_window->setPos(nextPos);
                }
            });
        }
    private:
        std::unique_ptr<Layout::Window::Window> m_window;
        s3d::Font m_font;
        Vec2 m_pos{};
        Vec2 m_size{};
    };
}
namespace abyss::Debug
{
    class WatchViewer::Impl
    {
    public:
        Impl():
            m_viewer(std::make_unique<ViewerCore>())
        {}

        void update()
        {
            m_buffer.clear();
        }

        void draw() const
        {
            if (m_viewer) {
                m_viewer->draw(m_buffer);
            }
        }

        void print(const s3d::String& log)
        {
            m_buffer.emplace_back(log);
        }
    private:
        s3d::Array<WatchInfo> m_buffer;
        std::unique_ptr<ViewerCore> m_viewer;
    };
    WatchViewer::WatchViewer() :
        m_pImpl(std::make_shared<Impl>())
    {
    }

    void WatchViewer::update()
    {
        m_pImpl->update();
    }

    void WatchViewer::draw() const
    {
        m_pImpl->draw();
    }

    void WatchViewer::print(const s3d::String& log)
    {
        m_pImpl->print(log);
    }
}
#endif
