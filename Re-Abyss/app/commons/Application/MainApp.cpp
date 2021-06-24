#include "MainApp.hpp"
#include <abyss/commons/Constants.hpp>

namespace abyss
{
	bool MainApp::update()
	{
		return m_game.update();
	}

    MainApp::MainApp() :
		BaseApp(Constants::AppName, Constants::AppResolution)
	{
	}

    MainApp::~MainApp()
	{
	}
}