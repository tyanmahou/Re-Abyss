#include "Game.hpp"
#include <abyss/scenes/MainScene.hpp>

namespace abyss
{
	class Game::Impl
	{
		AppScene m_scene;

		void registerScene()
		{
			m_scene.add<MainScene>(SceneName::Main);
		}
	public:
		Impl()
		{
			this->registerScene();
		}

		bool update()
		{
			return m_scene.update();
		}
	};

	Game::Game() :
		m_pImpl(std::make_shared<Impl>())
	{}

	bool Game::Update()
	{
		return Instance()->m_pImpl->update();
	}
}