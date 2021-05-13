#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Enemy
{
	struct LaunSharkEntity;
}
namespace abyss::Actor::Enemy::LaunShark
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const LaunSharkEntity& entity);
	};
}