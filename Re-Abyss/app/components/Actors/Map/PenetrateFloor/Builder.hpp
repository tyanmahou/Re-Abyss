#pragma once
#include <abyss/modules/Actors/base/ActorObj.hpp>
#include <abyss/types/MapColInfo.hpp>

namespace abyss::Actor::Map::PenetrateFloor
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const s3d::Vec2& pos, const s3d::Vec2& size, bool canDown, ColDirection aroundFloor);
	};
}