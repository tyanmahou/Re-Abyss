#pragma once
#if ABYSS_DEBUG
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace abyss::Debug
{
	class IPauseEventTrigger
	{
	public:
		virtual ~IPauseEventTrigger() = default;
		virtual bool isPauseTrigger() const = 0;
		virtual bool isResumeTrigger() const
		{
			return this->isPauseTrigger();
		}

        virtual void onPause(){}
		virtual void onResume() {}
	};

	class Pause
	{
	public:
		Pause();

		Pause& setEvent(std::unique_ptr<IPauseEventTrigger>&& eventTrigger)
		{
			m_eventTrigger = std::move(eventTrigger);
			return *this;
		}
		bool isPause() const;
		bool isUpdate1f() const;

		void update();
	private:
		Coro::Fiber<> taskPause();
		Coro::Fiber<> taskUpdate1f();
	private:
		Coro::FiberHolder<> m_taskPause;
		Coro::FiberHolder<> m_taskUpdate1f;
		bool m_isPause = false;
		bool m_isUpdate1f = false;

		std::unique_ptr<IPauseEventTrigger> m_eventTrigger;
	};
}
#endif
