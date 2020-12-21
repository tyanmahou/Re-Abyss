#pragma once
#include <abyss/modules/Actors/base/IActor.hpp>

namespace abyss::Actor::Ooparts
{
	struct CommonBuilder
	{
		static void Build(IActor* pActor, IActor* parent);
	};
}