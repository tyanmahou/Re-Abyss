#pragma once
#include <abyss/components/base/Components.hpp>
#include <abyss/components/Cron/base/IJob.hpp>

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
		bool m_isBackBig = false;
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