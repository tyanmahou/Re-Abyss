#pragma once
#include <memory>

#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Actors/Map/MapActor.hpp>

namespace abyss
{
	class MapTranslator
	{
	public:
		static std::shared_ptr<Actor::Map::MapActor> ToActorPtr(const MapEntity&);
	};
}