#include <abyss/commons/Game/Game.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Game/RenderStateInitializer.hpp>
#include <abyss/scenes/SequenceManager.hpp>
#include <abyss/debugs/System/System.hpp>
#include <abyss/debugs/Menu/MenuUtil.hpp>

#if ABYSS_DEVELOP
#include <abyss/utils/Env/Env.hpp>
#include "Game.hpp"
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
            RenderStateInitializer::Init();
		}
        void onStart()
        {
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
        void onEnd()
        {
#if ABYSS_DEBUG
            Debug::MenuUtil::Save();
#endif
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

    void Game::onStart()
    {
        m_pImpl->onStart();
    }

	bool Game::update()
	{
		return m_pImpl->update();
	}
	void Game::onEnd()
	{
        m_pImpl->onEnd();
	}
}
