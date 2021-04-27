#pragma once
#include <abyss/modules/Actors/base/ActorObj.hpp>

namespace abyss::Actor::Ooparts
{
	struct CommonBuilder
	{
		static void Build(ActorObj* pActor, ActorObj* parent);
	};
}