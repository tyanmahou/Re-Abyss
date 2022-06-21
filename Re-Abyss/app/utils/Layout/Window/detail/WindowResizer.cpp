#include <abyss/utils/Layout/Window/detail/WindowResizer.hpp>

#include <abyss/utils/Layout/Window/detail/Constants.hpp>
#include <abyss/utils/Layout/Window/detail/Component.hpp>
#include <abyss/utils/Layout/Window/detail/WindowParam.hpp>
#include <Siv3D.hpp>

namespace abyss::Layout::Window::detail
{
    WindowResizer::WindowResizer(Component* pComp) :
        m_pComp(pComp)
    {
        grab().registHandler(this);
    }

    bool WindowResizer::onGrabPromise()
    {
        constexpr auto margin = Constants::Margin;
        auto& param = m_pComp->param();
        const auto rect = param.region;

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
        } else {
            return false;
        }
        return true;
    }

    void WindowResizer::onPreGrabCheck([[maybe_unused]] bool isPromised)
    {
    }

    s3d::Optional<GrabState> WindowResizer::onGrabCheck()
    {
        constexpr auto margin = Constants::Margin;
        auto& param = m_pComp->param();
        const auto rect = param.region;

        const RectF tl{ rect.x - margin, rect.y - margin, margin, margin };
        const RectF tr{ rect.x + rect.w, rect.y - margin, margin, margin };
        const RectF bl{ rect.x - margin, rect.y + rect.h, margin, margin };
        const RectF br{ rect.x + rect.w, rect.y + rect.h, margin, margin };

        const RectF    top{ rect.x, rect.y - margin , rect.w, margin };
        const RectF bottom{ rect.x, rect.y + rect.h , rect.w, margin };
        const RectF   left{ rect.x - margin, rect.y, margin, rect.h };
        const RectF  right{ rect.x + rect.w, rect.y, margin, rect.h };

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
        }
        return s3d::none;
    }
    void WindowResizer::onGrab([[maybe_unused]] GrabState state)
    {
    }
    void WindowResizer::onGrabUpdate(GrabState state)
    {
        constexpr auto minSize = Constants::WinMinSize;
        auto& param = m_pComp->param();

        const auto& grabPos = grab().grabPos();
        const auto& grabSize = grab().grabSize();

        auto delta = Cursor::PosF() - grab().grabCursorPos();

        if (state == GrabState::Top || state == GrabState::Tl || state == GrabState::Tr) {
            // 上
            if (grabSize.y - delta.y < minSize.y) {
                delta.y = -(minSize.y - grabSize.y);
            }
            param.pos.y = grabPos.y + delta.y;
            param.size.y = grabSize.y - delta.y;
        } else if (state == GrabState::Bottom || state == GrabState::Bl || state == GrabState::Br) {
            // 下
            if (grabSize.y + delta.y < minSize.y) {
                delta.y = minSize.y - grabSize.y;
            }
            param.size.y = grabSize.y + delta.y;
        }

        if (state == GrabState::Left || state == GrabState::Tl || state == GrabState::Bl) {
            // 左
            if (grabSize.x - delta.x < minSize.x) {
                delta.x = -(minSize.x - grabSize.x);
            }
            param.pos.x = grabPos.x + delta.x;
            param.size.x = grabSize.x - delta.x;
        } else if (state == GrabState::Right || state == GrabState::Tr || state == GrabState::Br) {
            // 右
            if (grabSize.x + delta.x < minSize.x) {
                delta.x = minSize.x - grabSize.x;
            }
            param.size.x = grabSize.x + delta.x;
        }
    }
    void WindowResizer::onGrabRelease()
    {
    }
    GrabCtrl& WindowResizer::grab() const
    {
        return m_pComp->grabCtrl();
    }
}
