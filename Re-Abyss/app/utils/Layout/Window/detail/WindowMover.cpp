#include <abyss/utils/Layout/Window/detail/WindowMover.hpp>

#include <abyss/utils/Layout/Window/detail/Constants.hpp>
#include <abyss/utils/Layout/Window/detail/Component.hpp>
#include <abyss/utils/Layout/Window/detail/WindowParam.hpp>

namespace abyss::Layout::Window::detail
{
    WindowMover::WindowMover(Component* pComp) :
        m_pComp(pComp)
    {
        grab().registHandler(this);
    }

    bool WindowMover::onGrabPromise()
    {
        auto& param = m_pComp->param();
        const auto rect = param.region;
        return rect.mouseOver();
    }

    void WindowMover::onPreGrabCheck([[maybe_unused]] bool isPromised)
    {
    }

    s3d::Optional<GrabState> WindowMover::onGrabCheck()
    {
        auto& param = m_pComp->param();
        const auto rect = param.region;
        if (rect.leftClicked()) {
            return GrabState::Move;
        }
        return s3d::none;
    }
    void WindowMover::onGrab([[maybe_unused]] GrabState state)
    {
    }
    void WindowMover::onGrabUpdate(GrabState state)
    {
        const auto& grabPos = grab().grabPos();
        auto& param = m_pComp->param();
        auto delta = Cursor::PosF() - grab().grabCursorPos();

        if (state == GrabState::Move) {
            // 移動
            param.pos = grabPos + delta;
        }
    }
    void WindowMover::onGrabRelease()
    {
    }
    GrabCtrl& WindowMover::grab() const
    {
        return m_pComp->grabCtrl();
    }
}
