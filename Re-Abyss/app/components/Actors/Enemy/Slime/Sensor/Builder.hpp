#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Enemy::Slime::Sensor
{
	struct Builder
	{
		static void Build(IActor* pActor, IActor* parent);
	};
}