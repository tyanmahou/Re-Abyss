#include <abyss/debugs/Pause/Pause.hpp>
#if ABYSS_DEBUG
#include <abyss/utils/Coro/Task/Wait.hpp>
#include <Siv3D.hpp>

namespace abyss::Debug
{
	Pause::Pause()
	{
		m_taskPause.reset(std::bind(&Pause::taskPause, this));
		m_taskUpdate1f.reset(std::bind(&Pause::taskUpdate1f, this));
	}
	bool Pause::isPause() const
	{
		return m_isPause;
	}
	bool Pause::isUpdate1f() const
	{
		return m_isUpdate1f;
	}
	void Pause::update()
	{
		m_taskPause.moveNext();
		m_taskUpdate1f.moveNext();
	}
	Coro::Task<> Pause::taskPause()
	{
		while (true) {
			co_await Coro::WaitUntil([this] {return m_eventTrigger->isPauseTrigger(); });
			co_yield{};
            m_eventTrigger->onPause();
			m_isPause = true;
			co_await Coro::WaitUntil([this] {return m_eventTrigger->isResumeTrigger(); });
			co_yield{};
			m_eventTrigger->onResume();
			m_isPause = false;
		}
		co_return;
	}
	Coro::Task<> Pause::taskUpdate1f()
	{
		while (true) {
			m_isUpdate1f = false;
			if (m_isPause && KeyF10.down()) {
				m_isUpdate1f = true;
			}
			co_yield{};
		}
		co_return;
	}
}
#endif
