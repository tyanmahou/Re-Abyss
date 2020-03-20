#include "Game.hpp"

#include <abyss/scenes/Main/MainScene.hpp>
#include <abyss/debug/DebugManager/DebugManager.hpp>

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
#if ABYSS_DEBUG
			DebugManager::Update();
#endif
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