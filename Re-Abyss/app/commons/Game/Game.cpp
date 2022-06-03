#include <abyss/commons/Game/Game.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/Resource/UserData/Migration/Migration.hpp>

#include <abyss/scenes/Root/RootScene.hpp>
#include <abyss/scenes/Splash/SplashScene.hpp>
#include <abyss/scenes/Title/TitleScene.hpp>
#include <abyss/scenes/SaveSelect/SaveSelectScene.hpp>
#include <abyss/scenes/Main/MainScene.hpp>
#include <abyss/scenes/ClearResult/ClearResultScene.hpp>

#include <abyss/debugs/System/System.hpp>

namespace abyss
{
	class Game::Impl
	{
		void registerScene()
		{
			m_scene.add<RootScene>(SceneName::Root);
			m_scene.add<SplashScene>(SceneName::Splash);
			m_scene.add<TitleScene>(SceneName::Title);
			m_scene.add<SaveSelectScene>(SceneName::SaveSelect);
			m_scene.add<MainScene>(SceneName::Main);
			m_scene.add<ClearResultScene>(SceneName::ClearResult);
		}

		void loadFont()
		{
			// フォントはデバッグモードでもリソースに入れてます

			// タイトル
			FontAsset::Register(U"pm12r-15", 15, U"/resources/fonts/PixelMplus12-Regular.ttf");
			FontAsset::Register(U"pm12r-20", 20, U"/resources/fonts/PixelMplus12-Regular.ttf");
			FontAsset::Register(U"pm12r-25", 25, U"/resources/fonts/PixelMplus12-Regular.ttf");

			FontAsset::Register(U"pm12b-12", 12, U"/resources/fonts/PixelMplus12-Bold.ttf");
			FontAsset::Register(U"pm12b-18", 18, U"/resources/fonts/PixelMplus12-Bold.ttf");
		}
		void setupDefaultRenderState()
		{
			Graphics2D::Internal::SetSamplerState(ShaderStage::Vertex, 0, SamplerState::ClampNearest);
			Graphics2D::Internal::SetSamplerState(ShaderStage::Pixel, 0, SamplerState::ClampNearest);
			Graphics2D::Internal::SetSamplerState(ShaderStage::Vertex, 1, SamplerState::BorderNearest);
			Graphics2D::Internal::SetSamplerState(ShaderStage::Pixel, 1, SamplerState::BorderNearest);
		}
	public:
		Impl()
		{
			// 初期設定
			this->setupDefaultRenderState();
			this->registerScene();
			this->loadFont();

			Resource::UserData::Migration::Update();
#if ABYSS_DEBUG
            Debug::System::SetContext(Debug::SystemContext{
                .pScene = &m_scene
            });
#endif
		}

		bool update()
		{
			InputManager::Update();

#if ABYSS_DEBUG
			return Debug::System::Apply([this] {
				return m_scene.update();
			});
#else
			return m_scene.update();
#endif
		}
	private:
		AppScene m_scene;
	};

	Game::Game() :
		m_pImpl(std::make_unique<Impl>())
	{
	}

	Game::~Game()
	{}

	bool Game::update()
	{
		return m_pImpl->update();
	}
}
