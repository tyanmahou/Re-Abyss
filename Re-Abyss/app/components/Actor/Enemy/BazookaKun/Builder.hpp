#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Actor/Enemy/BazookaKunEntity.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const BazookaKunEntity& entity);
	};
}
