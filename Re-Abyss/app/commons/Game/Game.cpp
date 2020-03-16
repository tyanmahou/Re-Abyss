#include "Game.hpp"
#include <abyss/scenes/Main/MainScene.hpp>

namespace abyss
{
	class Game::Impl
	{
		AppScene m_scene;
		InputManager m_input;
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

		const InputManager& input() const
		{
			return m_input;
		}
	};

	Game::Game() :
		m_pImpl(std::make_shared<Impl>())
	{}

	bool Game::Update()
	{
		return Instance()->m_pImpl->update();
	}
    const InputManager& Game::Input()
    {
		return Instance()->m_pImpl->input();
    }
}