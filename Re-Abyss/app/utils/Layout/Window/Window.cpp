#include <abyss/utils/Layout/Window/Window.hpp>
#include <Siv3D.hpp>

namespace
{
    enum class GrabState
    {
        None,
        Top, Bottom, Left, Right,
        Tl, Tr, Bl, Br,
        Move,
        ScrollV,
        ScrollH,
    };

    s3d::Optional<CursorStyle> GetCursorStyle(GrabState grab)
    {
        switch (grab) {
        case GrabState::Tl:
            return CursorStyle::ResizeNWSE;
        case GrabState::Tr:
            return CursorStyle::ResizeNESW;
        case GrabState::Bl:
            return CursorStyle::ResizeNESW;
        case GrabState::Br:
            return CursorStyle::ResizeNWSE;
        case GrabState::Top:
            return CursorStyle::ResizeUpDown;
        case GrabState::Bottom:
            return CursorStyle::ResizeUpDown;
        case GrabState::Left:
            return CursorStyle::ResizeLeftRight;
        case GrabState::Right:
            s3d::Cursor::RequestStyle(CursorStyle::ResizeLeftRight);
            return CursorStyle::ResizeLeftRight;
        case GrabState::Move:
            return CursorStyle::Default;
        default:
            break;
        }
        return s3d::none;
    }

    constexpr double g_margin = 5.0;
    constexpr double g_scroolMargin = 15.0;
    constexpr double g_scroolBarSize = 20.0;
    constexpr Vec2 g_minSize{ g_scroolMargin * 2.0 + g_margin + g_scroolBarSize, g_scroolMargin * 3.0 + g_margin + g_scroolBarSize };

    struct ScrollBar
    {
        s3d::RectF barV(const RectF& region, const Vec2& contentSize) const
        {
            const Vec2& size = region.size;
            bool hasScrollH = contentSize.x > size.x;
            double minusH = hasScrollH ? g_scroolMargin : 0;
            return { region.x + region.w - g_scroolMargin, region.y, g_scroolMargin, size.y - minusH };
        }
        s3d::Optional<s3d::RectF> gripVOpt(const RectF& region, const Vec2& contentPos, const Vec2& contentSize) const
        {
            const Vec2& size = region.size;
            bool hasScrollV = contentSize.y > size.y;
            if (!hasScrollV) {
                return s3d::none;
            }
            return this->gripV(region, contentPos, contentSize);
        }
        s3d::RectF gripV(const RectF& region, const Vec2& contentPos, const Vec2& contentSize) const
        {
            auto bar = this->barV(region, contentSize);
            const Vec2& size = region.size;
            auto [hight, offsetMax] = this->gripVHightAndOffsetMax(region, contentSize);
            auto yOffs = s3d::Math::Lerp(
                0,
                offsetMax,
                s3d::Saturate(contentPos.y / (contentSize.y - size.y))
            );
            const double pushMargin = 1.0;
            return {
                bar.x + (5.0 - pushMargin),
                bar.y + bar.w + yOffs,
                bar.w - (5.0 - pushMargin) * 2.0,
                hight
            };
        }
        std::pair<double, double> gripVHightAndOffsetMax(const RectF& region, const Vec2& contentSize) const
        {
            auto bar = this->barV(region, contentSize);
            const Vec2& size = region.size;
            auto hight = s3d::Math::Lerp(
                g_scroolBarSize,
                bar.h - bar.w * 2.0,
                s3d::Saturate(size.y / contentSize.y)
            );
            return { hight, bar.h - bar.w * 2.0 - hight };
        }
        double toContentYFromGripDiff(const RectF& region, const Vec2& contentPos, const Vec2& contentSize, double diff) const
        {
            const double moveable = (contentSize.y - region.size.y);
            if (moveable <= 0) {
                return 0;
            }
            auto [hight, offsetMax] = this->gripVHightAndOffsetMax(region, contentSize);
            return s3d::Clamp(contentPos.y + diff * moveable / offsetMax, 0.0, moveable);
        }
        void drawV(const RectF& region, const Vec2& contentPos, const Vec2& contentSize, const ColorF& barColor, const ColorF& scrollColor) const
        {
            // スクロールバー
            RectF bar = this->barV(region, contentSize);
            bar.draw(barColor);
            {
                const double pushMargin = 1.0;
                //RectF(bar.pos, bar.w, bar.w).draw(ColorF(0.8, 1));
                Triangle(
                    { bar.x + bar.w * 0.5, bar.y + (5.0 - pushMargin) },
                    { bar.x + (4.0 - pushMargin), bar.y + bar.w - (5.0 - pushMargin) },
                    { bar.x + bar.w - (4.0 - pushMargin) , bar.y + bar.w - (5.0 - pushMargin) }
                ).draw(scrollColor);
            }
            {
                const Vec2 basePos{ bar.x, bar.y + bar.h - g_scroolMargin };
                const double pushMargin = 1.0;
                //RectF(basePos, bar.w, bar.w).draw(ColorF(0.8, 1));
                Triangle(
                    { bar.x + bar.w * 0.5, bar.y + bar.h - (5.0 - pushMargin) },
                    { bar.x + (4.0 - pushMargin), bar.y + bar.h - (bar.w - (5.0 - pushMargin)) },
                    { bar.x + bar.w - (4.0 - pushMargin), bar.y + bar.h - (bar.w - (5.0 - pushMargin)) }
                ).draw(scrollColor);
            }
            {
                RoundRect(this->gripV(region, contentPos, contentSize), 2.0)
                    .draw(scrollColor);
            }
        }
        s3d::RectF barH(const RectF& region, const Vec2& contentSize) const
        {
            const Vec2& size = region.size;
            bool hasScrollV = contentSize.y > size.y;
            double minusW = hasScrollV ? g_scroolMargin : 0;
            return { region.x, region.y + region.h - g_scroolMargin, size.x - minusW, g_scroolMargin };
        }
        s3d::Optional<s3d::RectF> gripHOpt(const RectF& region, const Vec2& contentPos, const Vec2& contentSize) const
        {
            const Vec2& size = region.size;
            bool hasScrollH = contentSize.x > size.x;
            if (!hasScrollH) {
                return s3d::none;
            }
            return this->gripH(region, contentPos, contentSize);
        }
        s3d::RectF gripH(const RectF& region, const Vec2& contentPos, const Vec2& contentSize) const
        {
            auto bar = this->barH(region, contentSize);
            const Vec2& size = region.size;
            auto [width, offsetMax] = this->gripHWidthAndOffsetMax(region, contentSize);
            auto xOffs = s3d::Math::Lerp(
                0,
                offsetMax,
                s3d::Saturate(contentPos.x / (contentSize.x - size.x))
            );
            const double pushMargin = 1.0;
            return{
                bar.x + bar.h + xOffs,
                bar.y + (5.0 - pushMargin),
                width,
                bar.h - (5.0 - pushMargin) * 2.0
            };
        }
        std::pair<double, double> gripHWidthAndOffsetMax(const RectF& region, const Vec2& contentSize) const
        {
            auto bar = this->barH(region, contentSize);
            const Vec2& size = region.size;
            auto width = s3d::Math::Lerp(
                g_scroolBarSize,
                bar.w - bar.h * 2.0,
                s3d::Saturate(size.x / contentSize.x)
            );
            return { width, bar.w - bar.h * 2.0 - width };
        }
        double toContentXFromGripDiff(const RectF& region, const Vec2& contentPos, const Vec2& contentSize, double diff) const
        {
            const double moveable = (contentSize.x - region.size.x);
            if (moveable <= 0) {
                return 0;
            }
            auto [hight, offsetMax] = this->gripHWidthAndOffsetMax(region, contentSize);
            return s3d::Clamp(contentPos.x + diff * moveable / offsetMax, 0.0, moveable);
        }
        void drawH(const RectF& region, const Vec2& contentPos, const Vec2& contentSize, const ColorF& barColor, const ColorF& scrollColor) const
        {
            const Vec2& size = region.size;
            // スクロールバー
            RectF bar = this->barH(region, contentSize);
            bar.draw(barColor);
            {
                const double pushMargin = 1.0;
                //RectF(bar.pos, bar.h, bar.h).draw(ColorF(0.8, 1));
                Triangle(
                    { bar.x + (5.0 - pushMargin), bar.y + bar.h * 0.5 },
                    { bar.x + bar.h - (5.0 - pushMargin), bar.y + (4.0 - pushMargin) },
                    { bar.x + bar.h - (5.0 - pushMargin) , bar.y + bar.h - (4.0 - pushMargin) }
                ).draw(scrollColor);
            }
            {
                const Vec2 basePos{ bar.x + bar.w - g_scroolMargin, bar.y };
                const double pushMargin = 1.0;
                //RectF(basePos, bar.h, bar.h).draw(ColorF(0.8, 1));
                Triangle(
                    { bar.x + bar.w - (5.0 - pushMargin), bar.y + bar.h * 0.5 },
                    { bar.x + bar.w - (bar.h - (5.0 - pushMargin)) , bar.y + (4.0 - pushMargin) },
                    { bar.x + bar.w - (bar.h - (5.0 - pushMargin)) , bar.y + bar.h - (4.0 - pushMargin) }
                ).draw(scrollColor);
            }
            {
                RoundRect(
                    this->gripH(region, contentPos, contentSize),
                    2.0
                ).draw(scrollColor);
            }
        }
        void draw(const RectF& region, const Vec2& contentPos, const Vec2& contentSize) const
        {
            const Vec2& size = region.size;
            bool hasScrollV = contentSize.y > size.y;
            bool hasScrollH = contentSize.x > size.x;
            const ColorF barColor = Color(240);
            const ColorF scrollColor = Color(133);

            if (hasScrollV) {
                this->drawV(region, contentPos, contentSize, barColor, scrollColor);
            }
            if (hasScrollH) {
                this->drawH(region, contentPos, contentSize, barColor, scrollColor);
            }
            if (hasScrollH && hasScrollV) {
                RectF(
                    region.x + region.w - g_scroolMargin,
                    region.y + region.h - g_scroolMargin,
                    g_scroolMargin,
                    g_scroolMargin
                ).draw(barColor);
            }
        }
    };
    struct WindowResizer
    {
    public:
        bool update(Vec2& pos, Vec2& size, Vec2& contentPos, const Vec2& contentSize)
        {
            if (!m_isGrab) {
                if (auto grabState = grabWatch(pos, size, contentPos, contentSize, g_margin)) {
                    m_isGrab = true;
                    m_grabState = *grabState;
                    m_grabPos = pos;
                    m_grabSize = size;
                    m_grabContentPos = contentPos;
                    m_grabCursorPos = s3d::Cursor::PosF();
                }
            } else if (!MouseL.pressed()) {
                m_isGrab = false;
            }
            if (m_isGrab) {
                this->grabUpdate(pos, size, contentPos, contentSize, g_minSize);
            }
            return m_isGrab;
        }
        const ScrollBar& scrollBar() const
        {
            return m_scroll;
        }
    private:
        s3d::Optional<GrabState> grabWatch(const Vec2& pos, const Vec2& size, Vec2& contentPos, const Vec2& contentSize, double margin)
        {
            const auto rect = RectF{ pos, size };

            const RectF tl{ rect.x - margin, rect.y - margin, margin, margin };
            const RectF tr{ rect.x + rect.w, rect.y - margin, margin, margin };
            const RectF bl{ rect.x - margin, rect.y + rect.h, margin, margin };
            const RectF br{ rect.x + rect.w, rect.y + rect.h, margin, margin };

            const RectF    top{ rect.x, rect.y - margin , rect.w, margin };
            const RectF bottom{ rect.x, rect.y + rect.h , rect.w, margin };
            const RectF   left{ rect.x - margin, rect.y, margin, rect.h };
            const RectF  right{ rect.x + rect.w, rect.y, margin, rect.h };

            if (tl.mouseOver()) {
                s3d::Cursor::RequestStyle(CursorStyle::ResizeNWSE);
            } else if (tr.mouseOver()) {
                s3d::Cursor::RequestStyle(CursorStyle::ResizeNESW);
            } else if (bl.mouseOver()) {
                s3d::Cursor::RequestStyle(CursorStyle::ResizeNESW);
            } else if (br.mouseOver()) {
                s3d::Cursor::RequestStyle(CursorStyle::ResizeNWSE);
            } else if (top.mouseOver() || bottom.mouseOver()) {
                s3d::Cursor::RequestStyle(CursorStyle::ResizeUpDown);
            } else if (left.mouseOver() || right.mouseOver()) {
                s3d::Cursor::RequestStyle(CursorStyle::ResizeLeftRight);
            }

            if (tl.leftClicked()) {
                return GrabState::Tl;
            } else if (tr.leftClicked()) {
                return GrabState::Tr;
            } else if (bl.leftClicked()) {
                return GrabState::Bl;
            } else if (br.leftClicked()) {
                return GrabState::Br;
            } else if (top.leftClicked()) {
                return GrabState::Top;
            } else if (bottom.leftClicked()) {
                return GrabState::Bottom;
            } else if (left.leftClicked()) {
                return GrabState::Left;
            } else if (right.leftClicked()) {
                return GrabState::Right;
            } else if (auto gripV = m_scroll.gripVOpt({ pos, size }, contentPos, contentSize); gripV && gripV->leftClicked()) {
                return GrabState::ScrollV;
            } else if (auto gripH = m_scroll.gripHOpt({ pos, size }, contentPos, contentSize); gripH && gripH->leftClicked()) {
                return GrabState::ScrollH;
            } else if (rect.leftClicked()) {
                return GrabState::Move;
            }
            return s3d::none;
        }
        void grabUpdate(Vec2& pos, Vec2& size, Vec2& contentPos, const Vec2& contentSize, const Vec2& minSize)
        {
            auto delta = Cursor::PosF() - m_grabCursorPos;

            ::GetCursorStyle(m_grabState).then([](CursorStyle stlye) {
                s3d::Cursor::RequestStyle(stlye);
            });
            if (m_grabState == GrabState::Move) {
                // 移動
                pos = m_grabPos + delta;
            } else if (m_grabState == GrabState::ScrollV) {
                // スクロール
                contentPos.y = m_scroll.toContentYFromGripDiff({ pos, size }, m_grabContentPos, contentSize, delta.y);
            } else if (m_grabState == GrabState::ScrollH) {
                // スクロール
                contentPos.x = m_scroll.toContentXFromGripDiff({ pos, size }, m_grabContentPos, contentSize, delta.x);
            } else {
                // リサイズ
                this->grabResize(pos, size, delta, minSize);
            }
        }
        void grabResize(Vec2& pos, Vec2& size, Vec2 delta, const Vec2& minSize)
        {
            if (m_grabState == GrabState::Top || m_grabState == GrabState::Tl || m_grabState == GrabState::Tr) {
                // 上
                if (m_grabSize.y - delta.y < minSize.y) {
                    delta.y = -(minSize.y - m_grabSize.y);
                }
                pos.y = m_grabPos.y + delta.y;
                size.y = m_grabSize.y - delta.y;
            } else if (m_grabState == GrabState::Bottom || m_grabState == GrabState::Bl || m_grabState == GrabState::Br) {
                // 下
                if (m_grabSize.y + delta.y < minSize.y) {
                    delta.y = minSize.y - m_grabSize.y;
                }
                size.y = m_grabSize.y + delta.y;
            }

            if (m_grabState == GrabState::Left || m_grabState == GrabState::Tl || m_grabState == GrabState::Bl) {
                // 左
                if (m_grabSize.x - delta.x < minSize.x) {
                    delta.x = -(minSize.x - m_grabSize.x);
                }
                pos.x = m_grabPos.x + delta.x;
                size.x = m_grabSize.x - delta.x;
            } else if (m_grabState == GrabState::Right || m_grabState == GrabState::Tr || m_grabState == GrabState::Br) {
                // 右
                if (m_grabSize.x + delta.x < minSize.x) {
                    delta.x = minSize.x - m_grabSize.x;
                }
                size.x = m_grabSize.x + delta.x;
            }
        }
    private:
        bool m_isGrab = false;
        s3d::Vec2 m_grabCursorPos{};
        s3d::Vec2 m_grabPos{};
        s3d::Vec2 m_grabSize{};
        GrabState m_grabState{};

        s3d::Vec2 m_grabContentPos{};

        ScrollBar m_scroll{};
    };
}
namespace abyss::Layout
{
    class Window::Handle
    {
    public:
        Handle(const s3d::Vec2& pos, const s3d::Vec2& size, const s3d::Vec2& contentSize) :
            m_pos(pos),
            m_size(size),
            m_contentSize(contentSize)
        {}
        void setBackground(const s3d::Optional<s3d::ColorF>& color)
        {
            m_backGroundColor = color;
        }
        void setFrameColor(const s3d::Optional<s3d::ColorF>& color)
        {
            m_frameColor = color;
        }
        void update()
        {
            m_resizer.update(m_pos, m_size, m_contentPos, m_contentSize);
        }
        [[nodiscard]] s3d::Rect region() const
        {
            return this->regionF().asRect();
        }
        [[nodiscard]] s3d::RectF regionF() const
        {
            return { m_pos, m_size };
        }
        s3d::ScopedViewport2D startViewport() const
        {
            return s3d::ScopedViewport2D{ this->region() };
        }
        s3d::Transformer2D transformer() const
        {
            return { Mat3x2::Translate(-m_contentPos), Mat3x2::Translate(m_pos - m_contentPos) };
        }
        s3d::RectF draw(std::function<void(const s3d::RectF&)> scene)
        {
            this->update();
            m_contentPos.x = s3d::Clamp(m_contentPos.x, 0.0, Max(m_contentSize.x - m_size.x, 0.0));
            m_contentPos.y = s3d::Clamp(m_contentPos.y, 0.0, Max(m_contentSize.y - m_size.y, 0.0));

            auto region = this->regionF();
            if (m_backGroundColor) {
                region.draw(*m_backGroundColor);
            }
            {
                auto t2d = this->transformer();
                auto viewport = this->startViewport();
                scene(region);
            }
            m_resizer.scrollBar().draw(region, m_contentPos, m_contentSize);

            if (m_frameColor) {
                region.drawFrame(0, 1, *m_frameColor);
            }
            return region;
        }
    private:
        s3d::Vec2 m_pos{};
        s3d::Vec2 m_size{};
        s3d::Vec2 m_contentPos{};
        s3d::Vec2 m_contentSize;
        s3d::Optional<ColorF> m_backGroundColor{};
        s3d::Optional<ColorF> m_frameColor{};
        WindowResizer m_resizer;
    };

    Window::Window() :
        Window({ 100, 100 })
    {}
    Window::Window(double w, double h) :
        Window(Vec2{ w, h })
    {}
    Window::Window(const s3d::Vec2& size) :
        Window({ 0, 0 }, size)
    {}
    Window::Window(const s3d::Vec2& pos, const s3d::Vec2& size) :
        Window(pos, size, size)
    {}
    Window::Window(
        const s3d::Vec2& pos,
        const s3d::Vec2& size,
        const s3d::Vec2& contentSize
    ) :
        m_pHandle(std::make_shared<Handle>(pos, size, contentSize))
    {}
    Window& Window::setBackGround(const s3d::Optional<s3d::ColorF>& color)
    {
        m_pHandle->setBackground(color);
        return *this;
    }
    Window& Window::setFrameColor(const s3d::Optional<s3d::ColorF>& color)
    {
        m_pHandle->setFrameColor(color);
        return *this;
    }
    s3d::RectF Window::draw(std::function<void(const s3d::RectF&)> scene) const
    {
        return m_pHandle->draw(std::move(scene));
    }
}
