#pragma once
#include <abyss/components/base/Components.hpp>
#include <abyss/components/Crons/base/IJob.hpp>

namespace abyss::Cron::BubbleGenerator
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
	struct ComponentTree<Cron::BubbleGenerator::Generator>
	{
		using Base = Cron::IJob;
	};
}