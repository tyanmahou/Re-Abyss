#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	struct KingDuxUtil
	{
	public:
		static Ref<ActorObj> BuildTentacle(ActorObj* pActor, const TentacleDesc& desc);

		static void SetVisible(ActorObj* pActor, bool isVisible);
	};
}