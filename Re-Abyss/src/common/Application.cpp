// windowのサイズを自由にするか
// #define USE_SCALABLE_WINDOW

#include "Application.hpp"

#include<Siv3D.hpp>
#include<HamFramework.hpp>

namespace
{
	enum class WindowSize
	{
		Default,
		Hurf,
		FullScrren
	};
	void ChangeWindowSize(WindowSize windowSize)
	{
		switch (windowSize)
		{
		case WindowSize::Default:
			Window::Resize(Window::BaseSize());
			break;
		case WindowSize::Hurf:
			Window::Resize(Window::BaseSize() / 2);
			break;
		case WindowSize::FullScrren:
			Window::SetFullscreen(true, {1280, 720});
			break;
		}
	}
	void ChangeWindowSize()
	{
		static WindowSize ws = WindowSize::Default;

		if (ws != WindowSize::FullScrren && Window::IsFullSceen()) {
			Window::SetFullscreen(false, { 1280, 720 });
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
		if (Input::KeyF7.clicked) {
			showFps ^= true;
		}
		if (showFps) {
			PutText(Profiler::FPS()).from(Vec2{ 0,0 });
		}
	}
}
namespace abyss
{
	Application::Application(const s3d::String& appName, s3d::Size windowSize)
	{
		Window::SetTitle(appName);
		Window::Resize(windowSize);
		Graphics::SetBackground(Palette::Black);
		System::SetExitEvent((Input::KeyAlt + Input::KeyF4).clicked | WindowEvent::CloseButton);
#ifdef USE_SCALABLE_WINDOW
		ham::ScalableWindow::Setup(windowSize);
#else
		Window::SetBaseSize(windowSize);
#endif
	}

	Application::~Application()
	{
	}

	bool Application::run() const
	{
		while (System::Update())
		{
			if (Input::KeyF4.clicked)
			{
				::ChangeWindowSize();
			}
			{
				const auto transformer = ScalableWindow::CreateTransformer();

				if (!this->update())
					return false;
			}
			ScalableWindow::DrawBlackBars();

			::DrawFps();
		}
		return true;
	}

}