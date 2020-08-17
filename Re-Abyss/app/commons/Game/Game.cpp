#include "Game.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Constants.hpp>

#include <abyss/scenes/Splash/SplashScene.hpp>
#include <abyss/scenes/Main/MainScene.hpp>
#include <abyss/scenes/Title/TitleScene.hpp>

#include <abyss/debugs/DebugManager/DebugManager.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace abyss
{
	class Game::Impl
	{
		AppScene m_scene;
		void registerScene()
		{
			m_scene.add<SplashScene>(SceneName::Splash);
			m_scene.add<TitleScene>(SceneName::Title);
			m_scene.add<MainScene>(SceneName::Main);
		}

		void loadFont()
		{
			FontAsset::Register(U"serif", 20, U"resources/fonts/PixelMplus12-Regular.ttf", FontStyle::Bitmap);
			FontAsset::Register(U"serifName", 17, U"resources/fonts/PixelMplus12-Bold.ttf", FontStyle::BoldBitmap);
		}
	public:
		Impl()
		{
			this->registerScene();
			this->loadFont();
		}

		bool update()
		{
			InputManager::Update();
#if ABYSS_DEBUG
			Debug::Log::ClearAndPrintCached();
			Debug::DebugManager::Update();
#endif
			return m_scene.update();
		}
	};

	Game::Game() :
		m_pImpl(std::make_unique<Impl>())
	{
		Graphics2D::SetSamplerState(0, SamplerState::ClampNearest);
	}

	bool Game::Update()
	{
		return Instance()->m_pImpl->update();
	}
}