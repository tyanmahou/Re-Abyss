#pragma once
#include <memory>

namespace abyss::Layout::Window::detail
{
    struct WindowParam;
    class GrabCtrl;
    class WindowResizer;
    class ScrollCtrl;
    class WindowMover;

    /// <summary>
    /// 機能統括
    /// </summary>
    class Component
    {
    public:
        Component(WindowParam& param);
        ~Component();

        WindowParam& param() const
        {
            return m_param;
        }
        GrabCtrl& grabCtrl() const
        {
            return *m_grabCtrl.get();
        }
        WindowResizer& resizer() const
        {
            return *m_resizer.get();
        }
        ScrollCtrl& scrollCtrl() const
        {
            return *m_scrollCtrl.get();
        }
        WindowMover& mover() const
        {
            return *m_mover.get();
        }
    private:
        WindowParam& m_param;
        std::unique_ptr<GrabCtrl> m_grabCtrl;
        std::unique_ptr<WindowResizer> m_resizer;
        std::unique_ptr<ScrollCtrl> m_scrollCtrl;
        std::unique_ptr<WindowMover> m_mover;
    };
}
