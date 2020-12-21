#pragma once
#include <abyss/modules/Cron/base/IJob.hpp>

namespace abyss::cron::BubbleGenerator
{
	class BubbleGeneratorJob : public IJob
	{
	public:
		Coro::Task<> onExecute() override;
	};
}