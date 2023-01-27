#pragma once

#include <abyss/modules/GameObject/Components.hpp>
#include <abyss/modules/Cron/base/IScheduler.hpp>

namespace abyss::Cron
{
	class IntervalTimeScheduler :
		public IComponent, 
		public IScheduler
	{
	public:
		IntervalTimeScheduler(Manager* pManager, const s3d::Duration& duration);

		Coro::Fiber<> execute(std::function<Coro::Fiber<>()> task) override;
	private:
		Manager* m_pManager;
		s3d::Duration m_duration;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Cron::IntervalTimeScheduler>
	{
		using Base = Cron::IScheduler;
	};
}