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
        SingletonManager m_singletonManager;

		Game m_game;
	};
}
