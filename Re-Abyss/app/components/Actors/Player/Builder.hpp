#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/Gimmick/StartPos/StartPosModel.hpp>

namespace abyss::Actor::Player
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const StartPosModel& startPos);
	};
}