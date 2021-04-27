#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/types/MapColInfo.hpp>

namespace abyss::Actor::Map
{
	struct CommonBuilder
	{
		static void Build(ActorObj* pActor, ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);
	};
}