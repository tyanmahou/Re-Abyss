#pragma once
#include <memory>
namespace abyss
{
	class WorldObject;
	struct MapInfoModel;

	class MapFactory
	{
	public:
		MapFactory() = default;
		std::shared_ptr<WorldObject> create(const MapInfoModel&);
	};
}