#pragma once
#include <abyss/modules/Actors/base/ActorObj.hpp>
#include <abyss/types/MapColInfo.hpp>

namespace abyss::Actor::Map::Ladder
{
	struct Builder
	{
		static void Build(ActorObj* pActor, ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);
	};
}