#include <abyss/debugs/Log/LogViewer.hpp>
#include <abyss/utils/DebugLog/DebugLog.hpp>
#include <abyss/utils/Layout/Window/Window.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::DebugLog;

    class ViewerCore : public IViewer
    {
        struct KindCustom
        {
            s3d::Texture icon;
            s3d::ColorF color;
        };
    public:
        ViewerCore() :
            m_font(16, Typeface::Regular),
            m_fontDetail(12, Typeface::Regular)
        {
            auto windowContext = Layout::Window::WindowContext{}
                .setBackGroundColor(s3d::none)
                .setFrameColor(s3d::none)
                .setScrollBarColor(ColorF(0, 0.5))
                .setScrollGripColor(ColorF(0.9))
                .setCanResize(false)
                .setIsResizeClampSceneSize(true)
                ;
            m_window = std::make_unique<Layout::Window::Window>(windowContext);
            m_kindCustom[LogKind::Info] = KindCustom{
                .icon = Texture(Emoji(U"🗨️")),
                .color = ColorF(0, 0.2)
            };
            m_kindCustom[LogKind::Warn] = KindCustom{
                .icon = Texture(Emoji(U"⚠️")),
                .color = ColorF(1.0, 1.0, 0, 0.2)
            };
            m_kindCustom[LogKind::Error] = KindCustom{
                .icon = Texture(Emoji(U"❌")),
                .color = ColorF(1.0, 0, 0, 0.2)
            };
            m_kindCustom[LogKind::Load] = KindCustom{
                .icon = Texture(Emoji(U"❕")),
                .color = ColorF(1.0, 0.0, 1.0, 0.2)
            };
        }

        void draw(const s3d::Array<LogInfo>& logs) const override
        {
            if (logs.isEmpty()) {
                return;
            }
            m_window->draw([&](const RectF& sceneScreen) {

                s3d::ScopedRenderStates2D sampler(s3d::SamplerState::ClampLinear);

                constexpr Vec2 iconSize{ 20,20 };
                constexpr double iconMargin = 5.0;
                // ウィンドウ幅
                double width = 0;
                for (const auto& log : logs) {
                    width = s3d::Max(width, m_font(log.log()).region().w);
                }
                width += iconSize.x + iconMargin;
                width += 10;

                Vec2 pos{ 0, 0 };
                for (const auto& log : logs) {
                    const auto& custom = m_kindCustom.at(log.kind());
                    auto region = m_font(log.log()).region();
                    region.w = width;
                    region.h = s3d::Max(region.h, iconSize.y);

                    auto area = RectF(pos, region.size);
                    if (area.y <= sceneScreen.y + sceneScreen.h && area.y + area.h >= sceneScreen.y) {
                        // 画面外の描画はしない
                        area.draw(custom.color);

                        custom.icon.resized(iconSize).draw(pos);
                        auto logPos = pos;
                        logPos.x += iconSize.x + iconMargin;
                        m_font(log.log()).draw(logPos);
                    }
                    pos.y += region.h;

                    //if (area.mouseOver()) {
                    //    auto detailRegion = m_fontDetail(log.location()).region(pos);
                    //    detailRegion.draw(ColorF(0.2, 0.2));
                    //    m_fontDetail(log.location()).draw(pos);
                    //    pos = detailRegion.bl();
                    //}
                }

                bool isScrollButtom = m_window->isScrollBottom();
                m_window->setSize({ s3d::Min<double>(width, s3d::Scene::Width()), s3d::Min<double>(pos.y, s3d::Scene::Height()) });
                m_window->setSceneSize({ width, pos.y });
                if (isScrollButtom) {
                    m_window->setScenePosToBottom();
                }
            });
        }
    private:
        std::unique_ptr<Layout::Window::Window> m_window;

        s3d::Font m_font;
        s3d::Font m_fontDetail;
        s3d::HashTable<LogKind, KindCustom> m_kindCustom;
    };
}
namespace abyss::Debug
{
    class LogViewer::Impl
    {
    public:
        Impl()
        {
            m_log.setViewer<::ViewerCore>();
        }
        void update()
        {
            m_log.update();
        }
        void draw() const
        {
            m_log.draw();
        }
        DebugLog::DebugLog& log()
        {
            return m_log;
        }
    private:
        DebugLog::DebugLog m_log;
    };

    LogViewer::LogViewer():
        m_pImpl(std::make_shared<Impl>())
    {}

    void LogViewer::update()
    {
        m_pImpl->update();
    }
    void LogViewer::draw() const
    {
        m_pImpl->draw();
    }
    void LogViewer::printInfo(const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->log().print(LogKind::Info, log, location);
    }
    void LogViewer::printInfoUpdate(const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->log().printUpdate(LogKind::Info, log, location);
    }
    void LogViewer::printWarn(const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->log().print(LogKind::Warn, log, location);
    }
    void LogViewer::printWarnUpdate(const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->log().printUpdate(LogKind::Warn, log, location);
    }
    void LogViewer::printError(const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->log().print(LogKind::Error, log, location);
    }
    void LogViewer::printErrorUpdate(const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->log().printUpdate(LogKind::Error, log, location);
    }
    void LogViewer::printLoad(const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->log().print(LogKind::Load, log, location);
    }
    void LogViewer::printLoadUpdate(const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->log().printUpdate(LogKind::Load, log, location);
    }
    void LogViewer::clear()
    {
        m_pImpl->log().clear();
    }
}

