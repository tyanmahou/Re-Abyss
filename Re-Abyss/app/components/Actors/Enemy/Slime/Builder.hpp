#pragma once
#include <abyss/modules/Actors/base/ActorObj.hpp>

namespace abyss
{
	struct SlimeEntity;
}
namespace abyss::Actor::Enemy::Slime
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const SlimeEntity& entity);
	};
}