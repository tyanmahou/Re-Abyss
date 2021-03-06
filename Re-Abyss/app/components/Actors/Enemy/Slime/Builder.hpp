#pragma once
#include <abyss/modules/Actors/base/IActor.hpp>

namespace abyss
{
	struct SlimeEntity;
}
namespace abyss::Actor::Enemy::Slime
{
	struct Builder
	{
		static void Build(IActor* pActor, const SlimeEntity& entity);
	};
}