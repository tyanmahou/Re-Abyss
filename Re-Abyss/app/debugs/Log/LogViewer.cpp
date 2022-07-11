#include <abyss/debugs/Log/LogViewer.hpp>
#if ABYSS_DEBUG
#include <abyss/debugs/Debug.hpp>
#include <abyss/utils/DebugLog/DebugLog.hpp>
#include <abyss/utils/Layout/Window/Window.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::DebugLog;

    bool IsVisible(LogKind kind)
    {
        switch (kind)
        {
        case LogKind::Info:
            return Debug::MenuUtil::IsDebug(Debug::DebugFlag::LogNormal);
        case LogKind::Warn:
            return Debug::MenuUtil::IsDebug(Debug::DebugFlag::LogWarn);
        case LogKind::Error:
            return Debug::MenuUtil::IsDebug(Debug::DebugFlag::LogError);
        case LogKind::Load:
            return Debug::MenuUtil::IsDebug(Debug::DebugFlag::LogLoad);
        default:
            break;
        }
        return true;
    }
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
            auto windowContext = Layout::Window::WindowContext{ Vec2{10, 10}, Vec2{300, 150} }
                .setBackGroundColor(ColorF(0, 0.1))
                .setFrameColor(s3d::none)
                .setScrollBarColor(ColorF(0, 0.5))
                .setScrollGripColor(ColorF(0.9))
                //.setCanResize(false)
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

        void draw(const s3d::Array<LogInfo>& logs) override
        {
            if (logs.isEmpty()) {
                return;
            }
            if (!Debug::MenuUtil::IsDebug(Debug::DebugFlag::LogIsVisible)) {
                return;
            }
            const LogInfo* pFocusLog = nullptr;
            m_window->draw([&](const RectF& sceneScreen) {

                s3d::ScopedRenderStates2D sampler(s3d::SamplerState::ClampLinear);

                constexpr Vec2 iconSize{ 20,20 };
                constexpr double iconMargin = 5.0;
                // ウィンドウ幅
                double width = 0;
                for (const auto& log : logs) {
                    width = s3d::Max(width, log.log().size() * m_font.spaceWidth() * 2);
                }
                width += iconSize.x + iconMargin;
                width += 10;

                Vec2 pos{ 0, 0 };
                Vec2 rectSize{ width, s3d::Max(static_cast<double>(m_font.height()), iconSize.y) };
                for (const auto& log : logs) {
                    const auto& custom = m_kindCustom.at(log.kind());
                    auto area = RectF(pos, rectSize);
                    if (area.y <= sceneScreen.y + sceneScreen.h && area.y + area.h >= sceneScreen.y) {
                        // 画面外の描画はしない
                        bool isFocus = false;
                        if (!pFocusLog && sceneScreen.mouseOver() && area.mouseOver()) {
                            pFocusLog = &log;
                            isFocus = true;
                        }
                        auto color = custom.color;
                        if (isFocus) {
                            color.a *= 2.0;
                        }
                        area.draw(color);

                        custom.icon.resized(iconSize).draw(pos);
                        auto logPos = pos;
                        logPos.x += iconSize.x + iconMargin;
                        m_font(log.log()).draw(logPos);
                    }
                    pos.y += rectSize.y;
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
            });
            if (pFocusLog) {
                auto detailRegion = m_fontDetail(pFocusLog->location()).region(m_window->region().bl() + Vec2{ 0, 5 });
                auto pos = detailRegion.draw(ColorF(0, 0.5));
                m_fontDetail(pFocusLog->location()).draw(pos);
            }
        }
    private:
        std::unique_ptr<Layout::Window::Window> m_window;

        s3d::Font m_font;
        s3d::Font m_fontDetail;
        s3d::HashTable<LogKind, KindCustom> m_kindCustom;
        Vec2 m_size{};
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
    void LogViewer::printWarn(const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->log().print(LogKind::Warn, log, location);
    }
    void LogViewer::printError(const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->log().print(LogKind::Error, log, location);
    }
    void LogViewer::printLoad(const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->log().print(LogKind::Load, log, location);
    }
    void LogViewer::clear()
    {
        m_pImpl->log().clear();
    }
}
#endif
