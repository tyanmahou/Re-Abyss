#include <abyss/commons/Application/base/BaseApp.hpp>
#include <abyss/commons/Application/AppRunner.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    BaseApp::BaseApp(const s3d::String& appName, s3d::Size windowSize):
		m_windowCtrl(appName, windowSize)
	{}
    bool BaseApp::run()
    {
        AppRunner runner;
        return runner.run(this);
    }
}
