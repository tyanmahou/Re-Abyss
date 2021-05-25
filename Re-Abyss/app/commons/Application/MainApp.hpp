#pragma once
#include <abyss/commons/Application/base/IApplication.hpp>
#include <abyss/commons/Game/Game.hpp>
namespace abyss
{
	class MainApp : public IApplication
	{
	public:
        MainApp();
		~MainApp() override;
	private:
		bool update() override;
	private:
		Game m_game;
	};
}