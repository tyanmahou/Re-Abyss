#pragma once
#include <abyss/utils/Layout/Window/detail/GrabCtrl.hpp>

namespace abyss::Layout::Window::detail
{
	class Component;

	/// <summary>
	/// ウィンドウサイズ制御
	/// </summary>
	class WindowResizer : public IGrabHandler
	{
	public:
		WindowResizer(Component* pComp);
	public:
		bool onGrabPromise() override;
		void onPreGrabCheck(bool isPromised) override;
		s3d::Optional<GrabState> onGrabCheck() override;

		void onGrab(GrabState state);
		void onGrabUpdate(GrabState state);
		void onGrabRelease();
	private:
		GrabCtrl& grab() const;
	private:
		Component* m_pComp;
	};
}
