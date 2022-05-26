#pragma once
#if ABYSS_DEBUG
#include <abyss/utils/Coro/Task/TaskHolder.hpp>

namespace abyss::Debug
{
	class Pause
	{
	public:
		Pause();

		bool isPause() const;
		bool isUpdate1f() const;

		void update();
	private:
		Coro::Task<> taskPause();
		Coro::Task<> taskUpdate1f();
	private:
		Coro::TaskHolder<> m_taskPause;
		Coro::TaskHolder<> m_taskUpdate1f;
		bool m_isPause = false;
		bool m_isUpdate1f = false;
	};
}
#endif