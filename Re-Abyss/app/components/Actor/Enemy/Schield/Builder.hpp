#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Actor::Enemy
{
	struct SchieldEntity;
}

namespace abyss::Actor::Enemy::Schield
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const SchieldEntity& entity);
	};
}