#pragma once
#include <abyss/components/base/Components.hpp>
#include <abyss/components/Crons/base/IScheduler.hpp>

namespace abyss::Cron
{
	class OnceScheduler :
		public IComponent,
		public IScheduler
	{
	public:
		OnceScheduler() = default;

		Coro::Task<> execute(std::function<Coro::Task<>()> task) override;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Cron::OnceScheduler>
	{
		using Base = Cron::IScheduler;
	};
}