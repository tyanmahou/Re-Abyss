#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Land::Ladder
{
	struct Builder
	{
		static void Build(ActorObj* pActor, ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);
	};
}
