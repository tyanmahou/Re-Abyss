#pragma once
#include <abyss/modules/Actors/base/ActorObj.hpp>

namespace abyss
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