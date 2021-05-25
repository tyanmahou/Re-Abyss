#include "MainApp.hpp"

#include <Siv3D/Vector2D.hpp>
#include <Siv3D/String.hpp>

#include <abyss/commons/Constants.hpp>

namespace abyss
{
	bool MainApp::update()
	{
		return m_game.update();
	}

    MainApp::MainApp() :
		IApplication(Constants::AppName, Constants::AppResolution)
	{}

    MainApp::~MainApp()
	{
	}
}