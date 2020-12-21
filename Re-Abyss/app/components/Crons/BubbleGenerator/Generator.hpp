#pragma once
#include <abyss/components/base/Components.hpp>
#include <abyss/components/Crons/base/IJob.hpp>

namespace abyss::cron::BubbleGenerator
{
	class Generator : 
		public IComponent,
		public IJob
	{
	public:
		Generator(Manager* pManager);

		Coro::Task<> onExecute() override;
	private:
		Manager* m_pManager;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<cron::BubbleGenerator::Generator>
	{
		using Base = cron::IJob;
	};
}