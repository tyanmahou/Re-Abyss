#pragma once
#include <abyss/components/base/Components.hpp>
#include <abyss/components/Cron/base/IJob.hpp>

namespace abyss::Cron::BubbleGenerator
{
	class Generator final: 
		public IComponent,
		public IJob
	{
	public:
		Generator(Manager* pManager);

		void onStart() override;
		Coro::Task<> onExecute() override;
	private:
		Ref<Effect::EffectObj> buildEffect();
	private:
		Manager* m_pManager;
		s3d::int32 m_count = 0;
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