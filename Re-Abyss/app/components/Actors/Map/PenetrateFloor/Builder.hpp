#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/types/MapColInfo.hpp>

namespace abyss::Actor::Map::PenetrateFloor
{
	struct Builder
	{
		static void Build(IActor* pActor, const s3d::Vec2& pos, const s3d::Vec2& size, bool canDown, ColDirection aroundFloor);
	};
}