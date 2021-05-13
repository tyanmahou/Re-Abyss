#pragma once
#include <memory>

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Map
{
	class MapTranslator
	{
	public:
		Ref<Actor::ActorObj> buildActor(World& world, const MapEntity& entity);
	};
}