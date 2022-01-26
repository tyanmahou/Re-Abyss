#include <abyss/utils/Windows/CustomWindowProc/CustomWindowProc.hpp>
#include <Siv3D.hpp>

namespace
{
	using namespace abyss::Windows;
	HWND g_hWnd;
	LONG_PTR g_baseProc = 0;

	s3d::HashTable<CustomWindowProc::Impl*, CustomWindowProc::Callback_t> g_callbacks;

	LRESULT CALLBACK CustomWindowProcImpl(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		for (auto&& [_, callback] : g_callbacks) {
			if (!callback) {
				continue;
			}
			if (auto result = callback(hWnd, message, wParam, lParam); result) {
				return result.value();
			}
		}
		return CallWindowProc(reinterpret_cast<WNDPROC>(g_baseProc), hWnd, message, wParam, lParam);
	}
}

namespace abyss::Windows
{
	class CustomWindowProc::Impl
	{
	public:
		Impl()
		{
			if (g_callbacks.empty() && !g_baseProc) {
				g_hWnd = static_cast<HWND>(s3d::Platform::Windows::Window::GetHWND());
				g_baseProc = ::SetWindowLongPtr(g_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(::CustomWindowProcImpl));
			}
			g_callbacks[this] = nullptr;
		}

		~Impl()
		{
			g_callbacks.erase(this);
			if (g_callbacks.empty() && g_baseProc) {
				::SetWindowLongPtr(g_hWnd, GWLP_WNDPROC, g_baseProc);
			}
		}
	};
	CustomWindowProc::CustomWindowProc() :
		m_pImpl(std::make_shared<Impl>())
	{}

	CustomWindowProc::CustomWindowProc(const Callback_t& callback) :
		CustomWindowProc()
	{
		this->setCallback(callback);
	}

	void CustomWindowProc::setCallback(const Callback_t& callback)
	{
		g_callbacks[m_pImpl.get()] = callback;
	}
}
