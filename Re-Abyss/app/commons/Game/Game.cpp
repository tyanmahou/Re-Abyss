#include "Game.hpp"

#include <abyss/scenes/Main/MainScene.hpp>
#include <abyss/debugs/DebugManager/DebugManager.hpp>
#include <abyss/debugs/DebugLog/DebugLog.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

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
			InputManager::Update();

			WorldTime::Update();
#if ABYSS_DEBUG
			DebugLog::ClearAndPrintCached();
			DebugManager::Update();
#endif

			return m_scene.update();
		}
	};

	Game::Game() :
		m_pImpl(std::make_shared<Impl>())
	{
		Graphics2D::SetSamplerState(0, SamplerState::ClampNearest);
	}

	bool Game::Update()
	{
		return Instance()->m_pImpl->update();
	}
}