#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/types/MapColInfo.hpp>

namespace abyss::Actor::Map
{
	struct CommonBuilder
	{
		static void Build(IActor* pActor, ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);
	};
}