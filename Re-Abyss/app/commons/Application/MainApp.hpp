#pragma once
#include <abyss/commons/Application/base/BaseApp.hpp>
#include <abyss/commons/Game/Game.hpp>
#include <abyss/commons/SingletonManager/SingletonManager.hpp>

namespace abyss
{
	class MainApp : public BaseApp
	{
	public:
        MainApp();
		~MainApp() override;
	private:
		bool update() override;
	private:
		Game m_game;
		SingletonManager m_singletonManager;
	};
}