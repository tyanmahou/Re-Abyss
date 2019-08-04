#include "Game.hpp"
#include "../util/TimeUtil.hpp"
#include "../scene/MainScene.hpp"
#include <HamFramework.hpp>
namespace
{
	void RegisterAddon()
	{
		Addon::Register<abyss::TimeUtil>();
	}
}
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

			::RegisterAddon();
		}

		bool update()
		{	
			return m_scene.updateAndDraw();
		}
	};
	Game::Game():
		m_pImpl(std::make_shared<Impl>())
	{}
	bool Game::Update()
	{
		return Instance()->m_pImpl->update();
	}
}