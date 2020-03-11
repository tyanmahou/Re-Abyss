#pragma once
#include <memory>

#include <abyss/commons/Fwd.hpp>
#include <abyss/models/actors/Map/MapActor.hpp>

namespace abyss
{
	class MapTranslator
	{
	public:
		static std::shared_ptr<MapActor> ToActorPtr(const MapEntity&);
	};
}