#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Enemy
{
	struct IkalienEntity;
}
namespace abyss::Actor::Enemy::Ikalien
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const IkalienEntity& entity);
	};
}