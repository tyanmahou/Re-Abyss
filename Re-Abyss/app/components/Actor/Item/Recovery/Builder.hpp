#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Item
{
	struct RecoveryEntity;
}
namespace abyss::Actor::Item::Recovery
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const RecoveryEntity& entity);
	};
}