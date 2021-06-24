// Windowのサイズをスケーリング可能にするか
// #define USE_SCALABLE_WINDOW

#include "BaseApp.hpp"

#include <Siv3D.hpp>

namespace
{
	enum class WindowSize
	{
		ThreeSecond,
		FiveFourth,
		SixFifth,
		Default,
		FourFifth,
		ThreeFourth,
		Half,
		FullScrren,

		KIND_MAX
	};

	bool SetFullScreen(bool isFullScreen)
	{
		return Window::SetFullscreen(isFullScreen, unspecified, WindowResizeOption::KeepSceneSize);
	}
	void ChangeWindowSize(WindowSize windowSize)
	{
		switch (windowSize)
		{
		case WindowSize::ThreeSecond:
			Window::Resize(Scene::Size() * 3 / 2, WindowResizeOption::KeepSceneSize);
			break;
		case WindowSize::FiveFourth:
			Window::Resize(Scene::Size() * 5 / 4, WindowResizeOption::KeepSceneSize);
			break;
		case WindowSize::SixFifth:
			Window::Resize(Scene::Size() * 6 / 5, WindowResizeOption::KeepSceneSize);
			break;
		case WindowSize::Default:
			Window::Resize(Scene::Size(), WindowResizeOption::KeepSceneSize);
			break;
		case WindowSize::FourFifth:
			Window::Resize(Scene::Size() * 4 / 5, WindowResizeOption::KeepSceneSize);
			break;
		case WindowSize::ThreeFourth:
			Window::Resize(Scene::Size() * 3 / 4, WindowResizeOption::KeepSceneSize);
			break;
		case WindowSize::Half:
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
		ws = static_cast<WindowSize>((static_cast<s3d::int32>(ws) + 1) % static_cast<s3d::int32>(WindowSize::KIND_MAX));

		::ChangeWindowSize(ws);
	}
}
namespace abyss
{
    BaseApp::BaseApp(const s3d::String& appName, s3d::Size windowSize)
	{
		Window::SetTitle(appName);
		Window::Resize(windowSize);

		Scene::SetBackground(Palette::Black);
		System::SetTerminationTriggers((KeyAlt + KeyF4).down() | UserAction::CloseButtonClicked);
#ifdef USE_SCALABLE_WINDOW
		Window::SetStyle(WindowStyle::Sizable);
#endif
	}

	bool BaseApp::run()
	{
		while (System::Update()) {

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