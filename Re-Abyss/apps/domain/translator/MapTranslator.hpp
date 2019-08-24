#pragma once
#include <memory>

namespace abyss
{
	class WorldObject;
	struct MapEntity;

	class MapTranslator
	{
	public:
		MapTranslator() = default;
		std::shared_ptr<WorldObject> create(const MapEntity&);
	};
}