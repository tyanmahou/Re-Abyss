#include "MapFactory.hpp"
#include "../objects/FloorModel.hpp"

#include "../MapInfoModel.hpp"
namespace abyss
{
	std::shared_ptr<WorldObject> MapFactory::create(const MapInfoModel& info)
	{
		if (info.type == FieldType::Floor) {
			return std::make_shared<FloorModel>(info.col, info.pos, info.size);
		}
		return nullptr;
	}
}