#include <abyss/debugs/System/System.hpp>
#if ABYSS_DEBUG

#include <abyss/utils/FPS/FrameRateHz.hpp>
#include <abyss/debugs/DebugManager/DebugManager.hpp>
#include <abyss/debugs/Log/Log.hpp>
#include <abyss/debugs/Menu/Menu.hpp>
#include <abyss/debugs/Profiler/Profiler.hpp>
#include <abyss/debugs/Pause/Pause.hpp>
#include <Siv3D.hpp>

namespace abyss::Debug
{
	class System::Impl
	{
	public:
		Impl()
		{
		}

		bool isPause() const
		{
			return m_pause.isPause();
		}

		void update()
		{
			// ログ更新
			Debug::LogUpdater::Update();
			// FPS制御
			FrameRateHz::Sleep();
			// プロファイラ
			Debug::Profiler::Print();

			Debug::DebugManager::Update();
			m_pause.update();
		}

		void draw() const
		{
			if (this->isPause()) {
				m_pause.captureDraw();
				Debug::Menu::Update();
			}
		}
	private:
		Pause m_pause;
	};
	System::System() :
		m_pImpl(std::make_unique<Impl>())
	{
	}

	System::~System()
	{
	}

	void System::update()
	{
		m_pImpl->update();
	}
	void System::draw() const
	{
		m_pImpl->draw();
	}
	bool System::isPause() const
	{
		return m_pImpl->isPause();
	}
}
#endif