#include <abyss/utils/Layout/Window/Window.hpp>
#include <Siv3D.hpp>

namespace
{
    struct WindowParam
    {
        union {
            struct {
                s3d::Vec2 pos;
                s3d::Vec2 size;
            };
            struct {
                s3d::RectF region;
            };
        };
        s3d::Vec2 contentPos;
        s3d::Vec2 contentSize;
    };
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
        ScrollBar(const WindowParam& param) :
            m_param(param)
        {}
        s3d::RectF barV() const
        {
            bool hasScrollH = m_param.contentSize.x > m_param.size.x;
            double minusH = hasScrollH ? g_scroolMargin : 0;
            return { m_param.region.x + m_param.region.w - g_scroolMargin, m_param.region.y, g_scroolMargin, m_param.size.y - minusH };
        }
        bool isGripVClicked() const
        {
            bool hasScrollV = m_param.contentSize.y > m_param.size.y;
            if (!hasScrollV) {
                return false;
            }
            return this->gripV().leftClicked();
        }
        s3d::RectF gripV() const
        {
            auto bar = this->barV();
            auto [hight, offsetMax] = this->gripVHightAndOffsetMax();
            auto yOffs = s3d::Math::Lerp(
                0,
                offsetMax,
                s3d::Saturate(m_param.contentPos.y / (m_param.contentSize.y - m_param.size.y))
            );
            const double pushMargin = 1.0;
            return {
                bar.x + (5.0 - pushMargin),
                bar.y + bar.w + yOffs,
                bar.w - (5.0 - pushMargin) * 2.0,
                hight
            };
        }
        std::pair<double, double> gripVHightAndOffsetMax() const
        {
            auto bar = this->barV();
            auto hight = s3d::Math::Lerp(
                g_scroolBarSize,
                bar.h - bar.w * 2.0,
                s3d::Saturate(m_param.size.y / m_param.contentSize.y)
            );
            return { hight, bar.h - bar.w * 2.0 - hight };
        }
        double toContentYFromGripDiff(const s3d::Vec2& contentPos, double diff) const
        {
            const double moveable = (m_param.contentSize.y - m_param.region.size.y);
            if (moveable <= 0) {
                return 0;
            }
            auto [hight, offsetMax] = this->gripVHightAndOffsetMax();
            return s3d::Clamp(contentPos.y + diff * moveable / offsetMax, 0.0, moveable);
        }
        void drawV(const ColorF& barColor, const ColorF& scrollColor) const
        {
            // スクロールバー
            RectF bar = this->barV();
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
                RoundRect(this->gripV(), 2.0).draw(scrollColor);
            }
        }
        s3d::RectF barH() const
        {
            bool hasScrollV = m_param.contentSize.y > m_param.size.y;
            double minusW = hasScrollV ? g_scroolMargin : 0;
            return { m_param.region.x, m_param.region.y + m_param.region.h - g_scroolMargin, m_param.size.x - minusW, g_scroolMargin };
        }
        bool isGripHClicked() const
        {
            bool hasScrollH = m_param.contentSize.x > m_param.size.x;
            if (!hasScrollH) {
                return false;
            }
            return this->gripH().leftClicked();
        }
        s3d::RectF gripH() const
        {
            auto bar = this->barH();
            auto [width, offsetMax] = this->gripHWidthAndOffsetMax();
            auto xOffs = s3d::Math::Lerp(
                0,
                offsetMax,
                s3d::Saturate(m_param.contentPos.x / (m_param.contentSize.x - m_param.size.x))
            );
            const double pushMargin = 1.0;
            return{
                bar.x + bar.h + xOffs,
                bar.y + (5.0 - pushMargin),
                width,
                bar.h - (5.0 - pushMargin) * 2.0
            };
        }
        std::pair<double, double> gripHWidthAndOffsetMax() const
        {
            auto bar = this->barH();
            auto width = s3d::Math::Lerp(
                g_scroolBarSize,
                bar.w - bar.h * 2.0,
                s3d::Saturate(m_param.size.x / m_param.contentSize.x)
            );
            return { width, bar.w - bar.h * 2.0 - width };
        }
        double toContentXFromGripDiff(const s3d::Vec2& contentPos, double diff) const
        {
            const double moveable = (m_param.contentSize.x - m_param.size.x);
            if (moveable <= 0) {
                return 0;
            }
            auto [hight, offsetMax] = this->gripHWidthAndOffsetMax();
            return s3d::Clamp(contentPos.x + diff * moveable / offsetMax, 0.0, moveable);
        }
        void drawH(const ColorF& barColor, const ColorF& scrollColor) const
        {
            // スクロールバー
            RectF bar = this->barH();
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
                RoundRect(this->gripH(), 2.0).draw(scrollColor);
            }
        }
        void draw() const
        {
            const Vec2& size = m_param.size;
            bool hasScrollV = m_param.contentSize.y > size.y;
            bool hasScrollH = m_param.contentSize.x > size.x;
            const ColorF barColor = Color(240);
            const ColorF scrollColor = Color(133);

            if (hasScrollV) {
                this->drawV(barColor, scrollColor);
            }
            if (hasScrollH) {
                this->drawH(barColor, scrollColor);
            }
            if (hasScrollH && hasScrollV) {
                RectF(
                    m_param.region.x + m_param.region.w - g_scroolMargin,
                    m_param.region.y + m_param.region.h - g_scroolMargin,
                    g_scroolMargin,
                    g_scroolMargin
                ).draw(barColor);
            }
        }
    private:
        const WindowParam& m_param;
    };
    struct WindowResizer
    {
    public:
        WindowResizer(WindowParam& param) :
            m_param(param),
            m_scroll(param)
        {}
        bool update()
        {
            if (!m_isGrab) {
                if (auto grabState = grabWatch(g_margin)) {
                    m_isGrab = true;
                    m_grabState = *grabState;
                    m_grabPos = m_param.pos;
                    m_grabSize = m_param.size;
                    m_grabContentPos = m_param.contentPos;
                    m_grabCursorPos = s3d::Cursor::PosF();
                }
            } else if (!MouseL.pressed()) {
                m_isGrab = false;
            }
            if (m_isGrab) {
                this->grabUpdate(g_minSize);
            }
            return m_isGrab;
        }
        const ScrollBar& scrollBar() const
        {
            return m_scroll;
        }
    private:
        s3d::Optional<GrabState> grabWatch(double margin)
        {
            const auto rect = RectF{ m_param.pos, m_param.size };

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
            } else if (m_scroll.isGripVClicked()) {
                return GrabState::ScrollV;
            } else if (m_scroll.isGripHClicked()) {
                return GrabState::ScrollH;
            } else if (rect.leftClicked()) {
                return GrabState::Move;
            }
            return s3d::none;
        }
        void grabUpdate(const Vec2& minSize)
        {
            auto delta = Cursor::PosF() - m_grabCursorPos;

            ::GetCursorStyle(m_grabState).then([](CursorStyle stlye) {
                s3d::Cursor::RequestStyle(stlye);
            });
            if (m_grabState == GrabState::Move) {
                // 移動
                m_param.pos = m_grabPos + delta;
            } else if (m_grabState == GrabState::ScrollV) {
                // スクロール
                m_param.contentPos.y = m_scroll.toContentYFromGripDiff(m_grabContentPos, delta.y);
            } else if (m_grabState == GrabState::ScrollH) {
                // スクロール
                m_param.contentPos.x = m_scroll.toContentXFromGripDiff(m_grabContentPos, delta.x);
            } else {
                // リサイズ
                this->grabResize(delta, minSize);
            }
        }
        void grabResize(Vec2 delta, const Vec2& minSize)
        {
            if (m_grabState == GrabState::Top || m_grabState == GrabState::Tl || m_grabState == GrabState::Tr) {
                // 上
                if (m_grabSize.y - delta.y < minSize.y) {
                    delta.y = -(minSize.y - m_grabSize.y);
                }
                m_param.pos.y = m_grabPos.y + delta.y;
                m_param.size.y = m_grabSize.y - delta.y;
            } else if (m_grabState == GrabState::Bottom || m_grabState == GrabState::Bl || m_grabState == GrabState::Br) {
                // 下
                if (m_grabSize.y + delta.y < minSize.y) {
                    delta.y = minSize.y - m_grabSize.y;
                }
                m_param.size.y = m_grabSize.y + delta.y;
            }

            if (m_grabState == GrabState::Left || m_grabState == GrabState::Tl || m_grabState == GrabState::Bl) {
                // 左
                if (m_grabSize.x - delta.x < minSize.x) {
                    delta.x = -(minSize.x - m_grabSize.x);
                }
                m_param.pos.x = m_grabPos.x + delta.x;
                m_param.size.x = m_grabSize.x - delta.x;
            } else if (m_grabState == GrabState::Right || m_grabState == GrabState::Tr || m_grabState == GrabState::Br) {
                // 右
                if (m_grabSize.x + delta.x < minSize.x) {
                    delta.x = minSize.x - m_grabSize.x;
                }
                m_param.size.x = m_grabSize.x + delta.x;
            }
        }
    private:
        WindowParam& m_param;

        bool m_isGrab = false;
        s3d::Vec2 m_grabCursorPos{};
        s3d::Vec2 m_grabPos{};
        s3d::Vec2 m_grabSize{};
        GrabState m_grabState{};

        s3d::Vec2 m_grabContentPos{};

        ScrollBar m_scroll;
    };
}
namespace abyss::Layout
{
    class Window::Handle : public WindowParam
    {
    public:
        Handle(const s3d::Vec2& _pos, const s3d::Vec2& _size, const s3d::Vec2& _contentSize) :
            m_resizer(*this)
        {
            this->pos = _pos;
            this->size = _size;
            this->contentSize = _contentSize;
            this->contentPos = {};
        }
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
            m_resizer.update();

            contentPos.x = s3d::Clamp(contentPos.x, 0.0, Max(contentSize.x - size.x, 0.0));
            contentPos.y = s3d::Clamp(contentPos.y, 0.0, Max(contentSize.y - size.y, 0.0));
        }
        [[nodiscard]] s3d::Rect region() const
        {
            return this->regionF().asRect();
        }
        [[nodiscard]] s3d::RectF regionF() const
        {
            return WindowParam::region;
        }
        s3d::ScopedViewport2D startViewport() const
        {
            return s3d::ScopedViewport2D{ this->region() };
        }
        s3d::Transformer2D transformer() const
        {
            return { Mat3x2::Translate(-contentPos), Mat3x2::Translate(pos - contentPos) };
        }
        s3d::RectF draw(std::function<void(const s3d::RectF&)> scene)
        {
            this->update();

            auto region = this->regionF();
            if (m_backGroundColor) {
                region.draw(*m_backGroundColor);
            }
            {
                auto t2d = this->transformer();
                auto viewport = this->startViewport();
                scene(region);
            }
            m_resizer.scrollBar().draw();

            if (m_frameColor) {
                region.drawFrame(0, 1, *m_frameColor);
            }
            return region;
        }
    private:
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
