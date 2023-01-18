#include <abyss/commons/Game/Game.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/Resource/UserData/Migration/Migration.hpp>
#include <abyss/scenes/SequenceManager.hpp>
#include <abyss/debugs/System/System.hpp>

#if ABYSS_DEVELOP
#include <abyss/utils/Env/Env.hpp>
#endif

namespace abyss
{
	class Game::Impl
	{
	public:
		Impl()
		{
#if ABYSS_DEVELOP
            // 環境設定ファイル読み込み
            Env::Load();
#endif
			// 初期設定
			this->setupDefaultRenderState();
			this->loadFont();

			Resource::UserData::Migration::Update();
		}

		bool update()
		{
			InputManager::Update();

#if ABYSS_DEBUG
			return Debug::System::Apply([this] {
				return m_sequence.update();
			});
#else
			return m_sequence.update();
#endif
		}
    private:

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
	private:
        SequenceManager m_sequence;
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
