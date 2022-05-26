#include <abyss/debugs/Pause/Pause.hpp>
#if ABYSS_DEBUG
#include <abyss/utils/Coro/Task/Wait.hpp>
#include <Siv3D.hpp>

namespace abyss::Debug
{
	Pause::Pause()
	{
		m_task.reset(std::bind(&Pause::taskPause, this));
	}
	void Pause::update()
	{
		m_task.moveNext();
	}
	void Pause::captureDraw() const
	{
		m_capture.draw();
	}
	Coro::Task<> Pause::taskPause()
	{
		while (true) {
			co_await Coro::WaitUntil([] {return KeyF11.down(); });
			s3d::ScreenCapture::RequestCurrentFrame();
			co_yield{};
			s3d::ScreenCapture::GetFrame(m_capture);
			m_isPause = true;
			co_await Coro::WaitUntil([] {return KeyF11.down(); });
			co_yield{};
			m_isPause = false;
		}
		co_return;

	}
}
#endif