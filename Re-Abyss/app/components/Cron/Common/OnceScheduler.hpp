#pragma once
#include <abyss/modules/GameObject/Components.hpp>
#include <abyss/components/Cron/base/IScheduler.hpp>

namespace abyss::Cron
{
	class OnceScheduler :
		public IComponent,
		public IScheduler
	{
	public:
		OnceScheduler() = default;

		Coro::Fiber<> execute(std::function<Coro::Fiber<>()> task) override;
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