#pragma once
#include <memory>

namespace abyss
{
	class MapModel;
	struct MapEntity;

	class MapTranslator
	{
	public:
		MapTranslator() = default;
		std::shared_ptr<MapModel> create(const MapEntity&);
	};
}