#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Enemy
{
	struct RollingTakoEntity;
}
namespace abyss::Actor::Enemy::RollingTako
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const RollingTakoEntity& entity);
	};
}