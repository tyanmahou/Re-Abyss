#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Player/PlayerDesc.hpp>

namespace abyss::Actor::Player
{
	struct Builder
	{
		static void Build(
            ActorObj* pActor,
            const PlayerDesc& desc
        );
	};
}
