#pragma once
#include <memory>

namespace abyss
{
	class MapActor;
	struct MapEntity;

	class MapTranslator
	{
	public:
		MapTranslator() = default;
		std::shared_ptr<MapActor> create(const MapEntity&);
	};
}