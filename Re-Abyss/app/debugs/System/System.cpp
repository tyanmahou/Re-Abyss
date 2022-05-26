#include <abyss/debugs/System/System.hpp>
#if ABYSS_DEBUG

#include <abyss/utils/Coro/Task/TaskHolder.hpp>
#include <abyss/utils/Coro/Task/Wait.hpp>

#include <abyss/utils/FPS/FrameRateHz.hpp>
#include <abyss/debugs/DebugManager/DebugManager.hpp>
#include <abyss/debugs/Log/Log.hpp>
#include <abyss/debugs/Menu/Menu.hpp>
#include <abyss/debugs/Profiler/Profiler.hpp>

#include <Siv3D.hpp>

namespace abyss::Debug
{
	class System::Impl
	{
	public:
		Impl()
		{
			m_pauseUpdater.reset(std::bind(&Impl::taskPause, this));
		}

		bool isPause() const
		{
			return false;
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

			m_pauseUpdater.moveNext();
		}

		void draw() const
		{
			if (m_isPause) {
				m_capture.draw();

				Debug::Menu::Update();
			}
		}
	private:
		Coro::Task<> taskPause()
		{
			while (true) {
				co_await Coro::WaitUntil([] {return KeyF11.down(); });
				s3d::ScreenCapture::RequestCurrentFrame();
				co_yield{};
				s3d::ScreenCapture::GetFrame(m_capture);
				m_isPause = true;

				co_await Coro::WaitUntil([] {return KeyF11.down(); });
				m_isPause = false;
			}
			co_return;
		}
	private:
		Coro::TaskHolder<> m_pauseUpdater;
		bool m_isPause = false;

		s3d::DynamicTexture m_capture;
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