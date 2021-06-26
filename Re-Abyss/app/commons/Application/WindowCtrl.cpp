#include "WindowCtrl.hpp"
#include <Siv3D.hpp>

namespace
{
    using namespace abyss;

    bool SetFullScreen(bool isFullScreen)
    {
        return Window::SetFullscreen(isFullScreen, unspecified, WindowResizeOption::KeepSceneSize);
    }

    std::pair<int32, int32> ToRational(WindowSizeKind kind)
    {
        switch (kind) {
        case WindowSizeKind::ThreeSecond:
            return { 3,2 };
        case WindowSizeKind::FiveFourth:
            return { 5,4 };
        case WindowSizeKind::SixFifth:
            return { 6,5 };
        case WindowSizeKind::Default:
            return { 1,1 };
        case WindowSizeKind::FourFifth:
            return { 4,5 };
        case WindowSizeKind::ThreeFourth:
            return { 3,4 };
        case WindowSizeKind::Half:
            return { 1,2 };
        default:
            return { 1,1 };
        }
    }
}

namespace abyss
{
    WindowCtrl::WindowCtrl(const s3d::String& appName, s3d::Size windowSize, bool useScalable) :
        m_baseSceneSize(windowSize),
        m_windowSizeKind(WindowSizeKind::Default)
    {
        Window::SetTitle(appName);
        Window::Resize(windowSize);

        Scene::SetBackground(Palette::Black);
        System::SetTerminationTriggers((KeyAlt + KeyF4).down() | UserAction::CloseButtonClicked);

        if (useScalable) {
            Window::SetStyle(WindowStyle::Sizable);
        }
    }
    void WindowCtrl::changeWindowSize(WindowSizeKind kind)
    {
        switch (kind) {
        case WindowSizeKind::FullScrren:
            ::SetFullScreen(false);
            ::SetFullScreen(true);
            break;
        default:
        {
            auto [num, denom] = ::ToRational(kind);
            Window::Resize(m_baseSceneSize * num / denom, WindowResizeOption::KeepSceneSize);
        }
        break;
        }
        m_windowSizeKind = kind;
    }
    void WindowCtrl::changeWindowSizeNext()
    {
        auto next = static_cast<WindowSizeKind>((static_cast<s3d::int32>(m_windowSizeKind) + 1) % static_cast<s3d::int32>(WindowSizeKind::KIND_MAX));
        this->changeWindowSize(next);
    }
}
