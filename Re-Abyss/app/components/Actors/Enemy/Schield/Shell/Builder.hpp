#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Actor::Enemy::Schield::Shell
{
	struct Builder
	{
		static void Build(ActorObj* pActor, ActorObj* parent);
	};
}