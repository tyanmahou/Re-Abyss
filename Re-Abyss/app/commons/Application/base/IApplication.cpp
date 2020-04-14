// Windowのサイズをスケーリング可能にするか
// #define USE_SCALABLE_WINDOW

#include "IApplication.hpp"

#include <Siv3D.hpp>

namespace
{
	enum class WindowSize
	{
		Default,
		Hurf,
		FullScrren
	};

	bool SetFullScreen(bool isFullScreen)
	{
		return Window::SetFullscreen(isFullScreen, unspecified, WindowResizeOption::KeepSceneSize);
	}
	void ChangeWindowSize(WindowSize windowSize)
	{
		switch (windowSize)
		{
		case WindowSize::Default:
			Window::Resize(Scene::Size(), WindowResizeOption::KeepSceneSize);
			break;
		case WindowSize::Hurf:
			Window::Resize(Scene::Size() / 2, WindowResizeOption::KeepSceneSize);
			break;
		case WindowSize::FullScrren:
			::SetFullScreen(true);
			break;
		}
	}
	void ChangeWindowSize()
	{
		static WindowSize ws = WindowSize::Default;

		if (ws != WindowSize::FullScrren) {
			::SetFullScreen(false);
		}
		switch (ws)
		{
		case WindowSize::Default:
			ws = WindowSize::Hurf;
			break;
		case WindowSize::Hurf:
			ws = WindowSize::FullScrren;
			break;
		case WindowSize::FullScrren:
			ws = WindowSize::Default;
			break;
		default:
			break;
		}

		::ChangeWindowSize(ws);
	}

	void DrawFps()
	{
		static bool showFps = false;
		if (KeyF7.down()) {
			showFps ^= true;
		}
		if (showFps) {
			Print << Profiler::FPS();
		}
	}
}
namespace abyss
{
    IApplication::IApplication(const s3d::String& appName, s3d::Size windowSize)
	{
		Window::SetTitle(appName);
		Window::Resize(windowSize);

		Scene::SetBackground(Palette::Black);
		System::SetTerminationTriggers((KeyAlt + KeyF4).down() | UserAction::CloseButtonClicked);
#ifdef USE_SCALABLE_WINDOW
		Window::SetStyle(WindowState::Sizable);
#endif
	}

    IApplication::~IApplication()
	{
	}

	bool IApplication::run() const
	{
		while (System::Update()) {
			::DrawFps();

			if (KeyF4.down()) {
				::ChangeWindowSize();
			}

			if (!this->update()) {
				return false;
			}
		}
		return true;
	}
}