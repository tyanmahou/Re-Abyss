#include <abyss/utils/Layout/Window/detail/GrabCtrl.hpp>

#include <abyss/utils/Layout/Window/detail/Component.hpp>
#include <abyss/utils/Layout/Window/detail/WindowParam.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss::Layout::Window::detail;

    s3d::Optional<s3d::CursorStyle> GetCursorStyle(GrabState grab)
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
}
namespace abyss::Layout::Window::detail
{

    GrabCtrl::GrabCtrl(Component* pComp) :
        m_pComp(pComp)
    {
    }
    void GrabCtrl::update()
    {
        if (!m_isGrab) {
            bool isPromised = false;
            for (auto* handler : m_handlers) {
                if (handler->onGrabPromise()) {
                    isPromised = true;
                    m_promosedHandler = handler;
                    break;
                }
            }
            for (auto* handler : m_handlers) {
                handler->onPreGrabCheck(m_promosedHandler == handler);
            }
            if (isPromised) {
                if (auto grabState = m_promosedHandler->onGrabCheck()) {
                    m_isGrab = true;
                    m_grabState = *grabState;
                    m_grabPos = m_pComp->param().pos;
                    m_grabSize = m_pComp->param().size;
                    m_grabScenePos = m_pComp->param().scenePos;
                    m_grabCursorPos = s3d::Cursor::PosF();

                    m_promosedHandler->onGrab(m_grabState);
                }
            }
        } else if (!MouseL.pressed()) {
            m_isGrab = false;

            m_promosedHandler->onGrabRelease();
            m_promosedHandler = nullptr;
        }
        if (m_isGrab) {
            ::GetCursorStyle(m_grabState).then([](CursorStyle stlye) {
                s3d::Cursor::RequestStyle(stlye);
            });
            m_promosedHandler->onGrabUpdate(m_grabState);
        }
    }
    void GrabCtrl::registHandler(IGrabHandler* handler)
    {
        m_handlers << handler;
    }
}
