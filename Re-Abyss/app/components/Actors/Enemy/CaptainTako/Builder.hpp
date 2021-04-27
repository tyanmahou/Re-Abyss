#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
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