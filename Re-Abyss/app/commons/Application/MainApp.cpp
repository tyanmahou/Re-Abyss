#include "MainApp.hpp"

#include <Siv3D/Vector2D.hpp>
#include <Siv3D/String.hpp>

#include <abyss/commons/Game/Game.hpp>
#include <abyss/commons/Constants.hpp>

namespace abyss
{
	bool MainApp::update() const
	{
		return Game::Update();
	}

    MainApp::MainApp() :
		IApplication(Constants::AppName, Constants::AppResolution)
	{}

    MainApp::~MainApp()
	{}
}