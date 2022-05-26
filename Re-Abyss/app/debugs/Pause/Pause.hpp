#pragma once
#if ABYSS_DEBUG
#include <abyss/utils/Coro/Task/TaskHolder.hpp>
#include <Siv3D/DynamicTexture.hpp>

namespace abyss::Debug
{
	class Pause
	{
	public:
		Pause();

		bool isPause() const
		{
			return m_isPause;
		}

		void update();
		void captureDraw() const;

	private:
		Coro::Task<> taskPause();
	private:
		Coro::TaskHolder<> m_task;
		bool m_isPause = false;

		s3d::DynamicTexture m_capture;
	};
}
#endif