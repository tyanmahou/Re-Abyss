#pragma once
#include <memory>

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Land
{
	class LandTranslator
	{
	public:
		Ref<Actor::ActorObj> buildActor(Actors& actors, const LandEntity& entity);
	};
}
