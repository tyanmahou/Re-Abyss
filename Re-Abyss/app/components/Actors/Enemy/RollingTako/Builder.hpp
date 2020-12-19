#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss
{
	struct RollingTakoEntity;
}
namespace abyss::Actor::Enemy::RollingTako
{
	struct Builder
	{
		static void Build(IActor* pActor, const RollingTakoEntity& entity);
	};
}