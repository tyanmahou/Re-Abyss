#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
	struct Builder
	{
		static void Build(IActor* pActor, IActor* parent);
	};
}