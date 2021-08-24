#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Duration.hpp>

namespace abyss::Cron::FishGenerator
{
	struct Builder
	{
		static void Build(Batch* batch);
	};

	struct BuildOnce
	{
		static void Build(Batch* batch);
	};
}