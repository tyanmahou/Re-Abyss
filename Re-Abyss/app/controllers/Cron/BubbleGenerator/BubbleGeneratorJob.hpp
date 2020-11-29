#pragma once
#include <abyss/controllers/Cron/base/IJob.hpp>

namespace abyss::cron::BubbleGenerator
{
	class BubbleGeneratorJob : public IJob
	{
	public:
		Coro::Task onExecute() override;
	};
}