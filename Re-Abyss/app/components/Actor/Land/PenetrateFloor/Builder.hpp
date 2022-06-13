#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/types/MapColInfo.hpp>

namespace abyss::Actor::Land::PenetrateFloor
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const s3d::Vec2& pos, const s3d::Vec2& size, bool canDown, ColDirection aroundFloor);
	};
}
