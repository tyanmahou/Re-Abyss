#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Enemy
{
	struct CaptainTakoEntity;
}
namespace abyss::Actor::Enemy::CaptainTako
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const CaptainTakoEntity& entity);
	};
}