#pragma once

#include <abyss/components/base/Components.hpp>
#include <abyss/components/Crons/base/IScheduler.hpp>

namespace abyss::Cron
{
	class IntervalTimeScheduler :
		public IComponent, 
		public IScheduler
	{
	public:
		IntervalTimeScheduler(Manager* pManager, const s3d::Duration& duration);

		Coro::Task<> execute(std::function<Coro::Task<>()> task) override;
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