// Windowのサイズをスケーリング可能にするか
// #define USE_SCALABLE_WINDOW

#include "BaseApp.hpp"

#include <Siv3D.hpp>

namespace abyss
{
    BaseApp::BaseApp(const s3d::String& appName, s3d::Size windowSize):
		m_windowCtrl(appName, windowSize)
	{}

	bool BaseApp::run()
	{
		while (System::Update()) {

			if (KeyF4.down()) {
				m_windowCtrl.changeWindowSizeNext();
			}

			if (!this->update()) {
				return false;
			}
		}
		return true;
	}
}