#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Enemy
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