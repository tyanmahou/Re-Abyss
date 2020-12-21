#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Duration.hpp>

namespace abyss::cron::BubbleGenerator
{
	struct Builder
	{
		static void Build(Batch* batch);
	};

	struct BuildIntervalTime
	{
		static void Build(Batch* batch, const s3d::Duration& duration);
	};
}