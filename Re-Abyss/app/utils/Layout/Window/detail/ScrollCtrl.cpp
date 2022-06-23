#include <abyss/utils/Layout/Window/detail/ScrollCtrl.hpp>

#include <abyss/utils/Layout/Window/detail/Constants.hpp>
#include <abyss/utils/Layout/Window/detail/Component.hpp>
#include <abyss/utils/Layout/Window/detail/WindowParam.hpp>
#include <Siv3D.hpp>

namespace abyss::Layout::Window::detail
{
    class ScrollCtrl::View
    {
    public:
        View(const WindowParam& param) :
            m_param(param)
        {}

        s3d::RectF barV() const
        {
            double minusH = this->hasScrollH() ? Constants::ScrollMargin : 0;
            return {
                m_param.region.x + m_param.region.w - Constants::ScrollMargin, m_param.region.y,
                Constants::ScrollMargin, m_param.size.y - minusH
            };
        }
        s3d::RectF gripV(bool isFixMargin = true) const
        {
            auto bar = this->barV();
            auto [hight, offsetMax] = this->gripVHightAndOffsetMax();
            auto yOffs = s3d::Math::Lerp(
                0,
                offsetMax,
                s3d::Saturate(m_param.scenePos.y / (m_param.sceneSize.y - m_param.size.y))
            );
            double pushMargin = 1.0;
            if (!isFixMargin) {
                pushMargin = m_onTimeV;
            }
            return {
                bar.x + (5.0 - pushMargin),
                bar.y + bar.w + yOffs,
                bar.w - (5.0 - pushMargin) * 2.0,
                hight
            };
        }

        RectF upBtn() const
        {
            RectF bar = this->barV();
            return { bar.pos, bar.w, bar.w };
        }
        RectF downBtn() const
        {
            RectF bar = this->barV();
            const Vec2 basePos{ bar.x, bar.y + bar.h - Constants::ScrollMargin };
            return { basePos, bar.w, bar.w };
        }
        bool hasScrollV() const
        {
            return m_param.sceneSize.y > m_param.size.y;
        }
        bool isBarVClicked() const
        {
            if (!this->hasScrollV()) {
                return false;
            }
            return this->barV().leftClicked();
        }
        bool isBarVMouseOver() const
        {
            if (!this->hasScrollV()) {
                return false;
            }
            return this->barV().mouseOver();
        }
        bool isGripVClicked() const
        {
            if (!this->hasScrollV()) {
                return false;
            }
            return this->gripV().leftClicked();
        }
        std::pair<double, double> gripVHightAndOffsetMax() const
        {
            auto bar = this->barV();
            auto hight = s3d::Math::Lerp(
                Constants::ScrollBarSize,
                bar.h - bar.w * 2.0,
                s3d::Saturate(m_param.size.y / m_param.sceneSize.y)
            );
            return { hight, bar.h - bar.w * 2.0 - hight };
        }
        double toSceneYFromGripDiff(const s3d::Vec2& scenePos, double diff) const
        {
            const double moveable = (m_param.sceneSize.y - m_param.region.size.y);
            if (moveable <= 0) {
                return 0;
            }
            auto [hight, offsetMax] = this->gripVHightAndOffsetMax();
            return s3d::Clamp(scenePos.y + diff * moveable / offsetMax, 0.0, moveable);
        }
        bool isUpBtnMouseOver() const
        {
            if (!hasScrollV()) {
                return false;
            }
            return this->upBtn().mouseOver();
        }
        bool isUpBtnClicked() const
        {
            if (!hasScrollV()) {
                return false;
            }
            return this->upBtn().leftClicked();
        }
        bool isDownBtnMouseOver() const
        {
            if (!hasScrollV()) {
                return false;
            }
            return this->downBtn().mouseOver();
        }
        bool isDownBtnClicked() const
        {
            if (!hasScrollV()) {
                return false;
            }
            return this->downBtn().leftClicked();
        }

        void drawV(const ColorF& barColor, const ColorF& scrollColor) const
        {
            // スクロールバー
            RectF bar = this->barV();
            bar.draw(barColor);
            {
                const double pushMargin = m_pushUpBtn ? 0.0 : 1.0;
                Triangle(
                    { bar.x + bar.w * 0.5, bar.y + (5.0 - pushMargin) },
                    { bar.x + (4.0 - pushMargin), bar.y + bar.w - (5.0 - pushMargin) },
                    { bar.x + bar.w - (4.0 - pushMargin) , bar.y + bar.w - (5.0 - pushMargin) }
                ).draw(ColorF(scrollColor, m_onTimeV));
            }
            {
                const Vec2 basePos{ bar.x, bar.y + bar.h - Constants::ScrollMargin };
                const double pushMargin = m_pushDownBtn ? 0.0 : 1.0;
                Triangle(
                    { bar.x + bar.w * 0.5, bar.y + bar.h - (5.0 - pushMargin) },
                    { bar.x + (4.0 - pushMargin), bar.y + bar.h - (bar.w - (5.0 - pushMargin)) },
                    { bar.x + bar.w - (4.0 - pushMargin), bar.y + bar.h - (bar.w - (5.0 - pushMargin)) }
                ).draw(ColorF(scrollColor, m_onTimeV));
            }
            {
                RoundRect(this->gripV(false), 2.0).draw(scrollColor);
            }
        }

        s3d::RectF barH() const
        {
            double minusW = this->hasScrollV() ? Constants::ScrollMargin : 0;
            return {
                m_param.region.x, m_param.region.y + m_param.region.h - Constants::ScrollMargin,
                m_param.size.x - minusW, Constants::ScrollMargin
            };
        }

        s3d::RectF gripH(bool isFixMargin = true) const
        {
            auto bar = this->barH();
            auto [width, offsetMax] = this->gripHWidthAndOffsetMax();
            auto xOffs = s3d::Math::Lerp(
                0,
                offsetMax,
                s3d::Saturate(m_param.scenePos.x / (m_param.sceneSize.x - m_param.size.x))
            );
            double pushMargin = 1.0;
            if (!isFixMargin) {
                pushMargin = m_onTimeH;
            }
            return{
                bar.x + bar.h + xOffs,
                bar.y + (5.0 - pushMargin),
                width,
                bar.h - (5.0 - pushMargin) * 2.0
            };
        }

        RectF leftBtn() const
        {
            RectF bar = this->barH();
            return { bar.pos, bar.h, bar.h };
        }

        RectF rightBtn() const
        {
            RectF bar = this->barH();
            const Vec2 basePos{ bar.x + bar.w - Constants::ScrollMargin, bar.y };
            return { basePos, bar.h, bar.h };
        }

        bool hasScrollH() const
        {
            return m_param.sceneSize.x > m_param.size.x;
        }
        bool isBarHClicked() const
        {
            if (!this->hasScrollH()) {
                return false;
            }
            return this->barH().leftClicked();
        }
        bool isBarHMouseOver() const
        {
            if (!this->hasScrollH()) {
                return false;
            }
            return this->barH().mouseOver();
        }
        bool isGripHClicked() const
        {
            if (!this->hasScrollH()) {
                return false;
            }
            return this->gripH().leftClicked();
        }
        std::pair<double, double> gripHWidthAndOffsetMax() const
        {
            auto bar = this->barH();
            auto width = s3d::Math::Lerp(
                Constants::ScrollBarSize,
                bar.w - bar.h * 2.0,
                s3d::Saturate(m_param.size.x / m_param.sceneSize.x)
            );
            return { width, bar.w - bar.h * 2.0 - width };
        }
        double toSceneXFromGripDiff(const s3d::Vec2& scenePos, double diff) const
        {
            const double moveable = (m_param.sceneSize.x - m_param.size.x);
            if (moveable <= 0) {
                return 0;
            }
            auto [hight, offsetMax] = this->gripHWidthAndOffsetMax();
            return s3d::Clamp(scenePos.x + diff * moveable / offsetMax, 0.0, moveable);
        }
        bool isLeftBtnMouseOver() const
        {
            if (!hasScrollH()) {
                return false;
            }
            return this->leftBtn().mouseOver();
        }
        bool isLeftBtnClicked() const
        {
            if (!hasScrollH()) {
                return false;
            }
            return this->leftBtn().leftClicked();
        }
        bool isRightBtnMouseOver() const
        {
            if (!hasScrollH()) {
                return false;
            }
            return this->rightBtn().mouseOver();
        }
        bool isRightBtnClicked() const
        {
            if (!hasScrollH()) {
                return false;
            }
            return this->rightBtn().leftClicked();
        }
        void drawH(const ColorF& barColor, const ColorF& gripColor) const
        {
            // スクロールバー
            RectF bar = this->barH();
            bar.draw(barColor);
            {
                const double pushMargin = m_pushLeftBtn ? 0.0 : 1.0;
                Triangle(
                    { bar.x + (5.0 - pushMargin), bar.y + bar.h * 0.5 },
                    { bar.x + bar.h - (5.0 - pushMargin), bar.y + (4.0 - pushMargin) },
                    { bar.x + bar.h - (5.0 - pushMargin) , bar.y + bar.h - (4.0 - pushMargin) }
                ).draw(ColorF(gripColor, m_onTimeH));
            }
            {
                const Vec2 basePos{ bar.x + bar.w - Constants::ScrollMargin, bar.y };
                const double pushMargin = m_pushRightBtn ? 0.0 : 1.0;
                Triangle(
                    { bar.x + bar.w - (5.0 - pushMargin), bar.y + bar.h * 0.5 },
                    { bar.x + bar.w - (bar.h - (5.0 - pushMargin)) , bar.y + (4.0 - pushMargin) },
                    { bar.x + bar.w - (bar.h - (5.0 - pushMargin)) , bar.y + bar.h - (4.0 - pushMargin) }
                ).draw(ColorF(gripColor, m_onTimeH));
            }
            {
                RoundRect(this->gripH(false), 2.0).draw(gripColor);
            }
        }
        void draw(const ColorF& barColor, const ColorF& gripColor) const
        {
            const Vec2& size = m_param.size;
            bool hasScrollV = m_param.sceneSize.y > size.y;
            bool hasScrollH = m_param.sceneSize.x > size.x;

            if (hasScrollV) {
                this->drawV(barColor, gripColor);
            }
            if (hasScrollH) {
                this->drawH(barColor, gripColor);
            }
            if (hasScrollH && hasScrollV) {
                RectF(
                    m_param.region.x + m_param.region.w - Constants::ScrollMargin,
                    m_param.region.y + m_param.region.h - Constants::ScrollMargin,
                    Constants::ScrollMargin,
                    Constants::ScrollMargin
                ).draw(barColor);
            }
        }

        void updateOnTime(bool isBarVMouseOver, bool isBarHMouseOver, double dt)
        {
            if (isBarVMouseOver) {
                m_onTimeV = s3d::Saturate(m_onTimeV + dt * 5.0);
            } else {
                m_onTimeV = s3d::Saturate(m_onTimeV - dt * 2.0);
            }
            if (isBarHMouseOver) {
                m_onTimeH = s3d::Saturate(m_onTimeH + dt * 5.0);
            } else {
                m_onTimeH = s3d::Saturate(m_onTimeH - dt * 2.0);
            }
        }

        void pushUpBtn()
        {
            m_pushUpBtn = true;
        }
        void pushDownBtn()
        {
            m_pushDownBtn = true;
        }
        void pushLeftBtn()
        {
            m_pushLeftBtn = true;
        }
        void pushRightBtn()
        {
            m_pushRightBtn = true;
        }
        void resetPush()
        {
            m_pushUpBtn = false;
            m_pushDownBtn = false;
            m_pushLeftBtn = false;
            m_pushRightBtn = false;
        }
    private:
        const WindowParam& m_param;

        double m_onTimeV = 0;
        double m_onTimeH = 0;
        bool m_pushUpBtn = false;
        bool m_pushDownBtn = false;
        bool m_pushLeftBtn = false;
        bool m_pushRightBtn = false;
    };

    ScrollCtrl::ScrollCtrl(Component* pComp) :
        m_pComp(pComp),
        m_view(std::make_unique<View>(pComp->param()))
    {
        grab().registHandler(this);
    }
    void ScrollCtrl::update()
    {
        if (!m_pComp->param().canScroll) {
            return;
        }
        if (grab().isGrab()) {
            return;
        }
        if (m_pComp->param().region.mouseOver()) {
            constexpr double speed = 30.0;
            if (KeyShift.pressed()) {
                m_pComp->param().scenePos.x += Mouse::Wheel() * speed;
            } else {
                m_pComp->param().scenePos.y += Mouse::Wheel() * speed;
                m_pComp->param().scenePos.x += Mouse::WheelH() * speed;
            }
        }
    }
    void ScrollCtrl::draw(const ColorF& barColor, const ColorF& gripColor) const
    {
        m_view->draw(barColor, gripColor);
    }
    bool ScrollCtrl::onGrabPromise()
    {
        if (!m_pComp->param().canScroll) {
            return false;
        }
        if (m_view->isBarVMouseOver()) {
            return true;
        } else if (m_view->isBarHMouseOver()) {
            return true;
        }
        return false;
    }
    void ScrollCtrl::onPreGrabCheck(bool isPromised)
    {
        bool isBarVMouseOver = false;
        bool isBarHMouseOver = false;
        if (isPromised) {
            if (m_view->isBarVMouseOver()) {
                isBarVMouseOver = true;
            } else if (m_view->isBarHMouseOver()) {
                isBarHMouseOver = true;
            }
        }
        const double dt = Scene::DeltaTime();
        // スクロールバーの演出
        m_view->updateOnTime(isBarVMouseOver, isBarHMouseOver, dt);
    }
    s3d::Optional<GrabState> ScrollCtrl::onGrabCheck()
    {
        if (m_view->isUpBtnClicked()) {
            return GrabState::ScrollUp;
        } else if (m_view->isDownBtnClicked()) {
            return GrabState::ScrollDown;
        } else if (m_view->isGripVClicked()) {
            return GrabState::ScrollV;
        } else if (m_view->isBarVClicked()) {
            return GrabState::ScrollVTo;
        } else if (m_view->isLeftBtnClicked()) {
            return GrabState::ScrollLeft;
        } else if (m_view->isRightBtnClicked()) {
            return GrabState::ScrollRight;
        } else if (m_view->isGripHClicked()) {
            return GrabState::ScrollH;
        } else if (m_view->isBarHClicked()) {
            return GrabState::ScrollHTo;
        }
        return s3d::none;
    }
    void ScrollCtrl::onGrab(GrabState state)
    {
        m_waitTimer = 0;

        auto& param = m_pComp->param();
        const auto& grabCursorPos = grab().grabCursorPos();
        const auto& grabScenePos = grab().grabScenePos();

        if (state == GrabState::ScrollUp) {
            m_view->pushUpBtn();
            param.scenePos.y -= 1;
        } else if (state == GrabState::ScrollDown) {
            m_view->pushDownBtn();
            param.scenePos.y += 1;
        } else if (state == GrabState::ScrollLeft) {
            m_view->pushLeftBtn();
            param.scenePos.x -= 1;
        } else if (state == GrabState::ScrollRight) {
            m_view->pushRightBtn();
            param.scenePos.x += 1;
        } else if (state == GrabState::ScrollVTo) {
            auto moveDiff = m_view->gripVHightAndOffsetMax().first;
            const auto gripV = m_view->gripV();
            if (gripV.y > grabCursorPos.y) {
                moveDiff *= -1.0;
            } else if (gripV.y + gripV.h < grabCursorPos.y) {
                moveDiff *= 1.0;
            } else {
                moveDiff *= 0.0;
            }
            param.scenePos.y = m_view->toSceneYFromGripDiff(grabScenePos, moveDiff);
        } else if (state == GrabState::ScrollHTo) {
            auto moveDiff = m_view->gripHWidthAndOffsetMax().first;
            const auto gripH = m_view->gripH();
            if (gripH.x > grabCursorPos.x) {
                moveDiff *= -1.0;
            } else if (gripH.x + gripH.w < grabCursorPos.x) {
                moveDiff *= 1.0;
            } else {
                moveDiff *= 0.0;
            }
            param.scenePos.x = m_view->toSceneXFromGripDiff(grabScenePos, moveDiff);
        }
    }
    void ScrollCtrl::onGrabUpdate(GrabState state)
    {
        auto dt = Scene::DeltaTime();
        m_waitTimer += dt;

        auto& param = m_pComp->param();
        const auto& grabCursorPos = grab().grabCursorPos();
        const auto& grabScenePos = grab().grabScenePos();

        auto delta = Cursor::PosF() - grabCursorPos;

        if (state == GrabState::ScrollV) {
            // スクロール
            param.scenePos.y = m_view->toSceneYFromGripDiff(grabScenePos, delta.y);
        } else if (state == GrabState::ScrollH) {
            // スクロール
            param.scenePos.x = m_view->toSceneXFromGripDiff(grabScenePos, delta.x);
        } else if (state == GrabState::ScrollUp) {
            if (m_waitTimer >= 0.5) {
                if (m_view->isUpBtnMouseOver()) {
                    param.scenePos.y -= 200.0 * dt;
                }
            }
        } else if (state == GrabState::ScrollDown) {
            if (m_waitTimer >= 0.5) {
                if (m_view->isDownBtnMouseOver()) {
                    param.scenePos.y += 200.0 * dt;
                }
            }
        } else if (state == GrabState::ScrollLeft) {
            if (m_waitTimer >= 0.5) {
                if (m_view->isLeftBtnMouseOver()) {
                    param.scenePos.x -= 200.0 * dt;
                }
            }
        } else if (state == GrabState::ScrollRight) {
            if (m_waitTimer >= 0.5) {
                if (m_view->isRightBtnMouseOver()) {
                    param.scenePos.x += 200.0 * dt;
                }
            }
        } else if (state == GrabState::ScrollVTo) {
            if (m_waitTimer >= 0.5) {
                if (m_view->isBarVMouseOver()) {
                    auto moveDiff = m_view->gripVHightAndOffsetMax().first * 60.0 * dt;
                    const auto gripV = m_view->gripV();
                    if (gripV.y > grabCursorPos.y) {
                        moveDiff *= -1.0;
                    } else if (gripV.y + gripV.h < grabCursorPos.y) {
                        moveDiff *= 1.0;
                    } else {
                        moveDiff *= 0.0;
                    }
                    param.scenePos.y = m_view->toSceneYFromGripDiff(param.scenePos, moveDiff);
                }
            }
        } else if (state == GrabState::ScrollHTo) {
            if (m_waitTimer >= 0.5) {
                if (m_view->isBarHMouseOver()) {
                    auto moveDiff = m_view->gripHWidthAndOffsetMax().first * 60.0 * dt;
                    const auto gripH = m_view->gripH();
                    if (gripH.x > grabCursorPos.x) {
                        moveDiff *= -1.0;
                    } else if (gripH.x + gripH.w < grabCursorPos.x) {
                        moveDiff *= 1.0;
                    } else {
                        moveDiff *= 0.0;
                    }
                    param.scenePos.x = m_view->toSceneXFromGripDiff(param.scenePos, moveDiff);
                }
            }
        }
    }
    void ScrollCtrl::onGrabRelease()
    {
        m_view->resetPush();
    }
    GrabCtrl& ScrollCtrl::grab() const
    {
        return m_pComp->grabCtrl();
    }
}
