#include <abyss/commons/Application/MainApp.hpp>
#include <abyss/commons/Constants.hpp>

namespace abyss
{
    MainApp::MainApp() :
		BaseApp(Constants::AppName, Constants::AppResolution)
	{
	}

    MainApp::~MainApp()
	{
	}

    void MainApp::onStartup()
    {
        m_game.onStart();
    }

    bool MainApp::onUpdate()
    {
        if (KeyF4.down()) {
            m_windowCtrl.changeWindowSizeNext();
        }
        return m_game.update();
    }

    void MainApp::onShutdown()
    {
        m_game.onEnd();
    }
}
