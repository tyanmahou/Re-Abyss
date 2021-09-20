#include "Game.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/Resource/UserData/Migration/Migration.hpp>

#include <abyss/scenes/Splash/SplashScene.hpp>
#include <abyss/scenes/Title/TitleScene.hpp>
#include <abyss/scenes/SaveSelect/SaveSelectScene.hpp>
#include <abyss/scenes/Main/MainScene.hpp>

#include <abyss/utils/FPS/FrameRateHz.hpp>
#include <abyss/debugs/DebugManager/DebugManager.hpp>
#include <abyss/debugs/Log/Log.hpp>
#include <abyss/debugs/Menu/Menu.hpp>

namespace abyss
{
	class Game::Impl
	{
		AppScene m_scene;
		void registerScene()
		{
			m_scene.add<SplashScene>(SceneName::Splash);
			m_scene.add<TitleScene>(SceneName::Title);
			m_scene.add<SaveSelectScene>(SceneName::SaveSelect);
			m_scene.add<MainScene>(SceneName::Main);
		}

		void loadFont()
		{
			// フォントはデバッグモードでもリソースに入れてます
			FontAsset::Register(U"serif", 20, U"/resources/fonts/PixelMplus12-Regular.ttf", FontStyle::Bitmap);
			FontAsset::Register(U"serifName", 17, U"/resources/fonts/PixelMplus12-Bold.ttf", FontStyle::BoldBitmap);

			// タイトル
			FontAsset::Register(U"pm12r-20", 20, U"/resources/fonts/PixelMplus12-Regular.ttf", FontStyle::Bitmap);
			FontAsset::Register(U"pm12r-25", 25, U"/resources/fonts/PixelMplus12-Regular.ttf", FontStyle::Bitmap);

			FontAsset::Register(U"pm12b-12", 12, U"/resources/fonts/PixelMplus12-Bold.ttf", FontStyle::Bitmap);
			FontAsset::Register(U"pm12b-18", 18, U"/resources/fonts/PixelMplus12-Bold.ttf", FontStyle::Bitmap);
			// 
		}
	public:
		Impl()
		{
			this->registerScene();
			this->loadFont();

			Resource::UserData::Migration::Update();
#if ABYSS_DEBUG
			Debug::Menu::BindScene(&m_scene);
#endif
		}

		bool update()
		{
#if ABYSS_DEBUG
			FrameRateHz::Sleep();
			Debug::LogUpdater::Update();
			Debug::DebugManager::Update();
#endif

			InputManager::Update();

			return m_scene.update();
		}
	};

	Game::Game() :
		m_pImpl(std::make_unique<Impl>())
	{
		// 初期設定
		Graphics2D::Internal::SetSamplerState(ShaderStage::Vertex, 0, SamplerState::ClampNearest);
		Graphics2D::Internal::SetSamplerState(ShaderStage::Pixel, 0, SamplerState::ClampNearest);
	}

	Game::~Game()
	{}

	bool Game::update()
	{
		return m_pImpl->update();
	}
}