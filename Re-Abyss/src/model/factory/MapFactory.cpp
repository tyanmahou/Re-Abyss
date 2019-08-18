#include "MapFactory.hpp"
#include "../objects/PenetrateFloorModel.hpp"
#include "../objects/LadderModel.hpp"
#include "../MapInfoModel.hpp"
namespace abyss
{
	std::shared_ptr<WorldObject> MapFactory::create(const MapInfoModel& info)
	{
		if (info.type == FieldType::Floor) {
			return std::make_shared<FloorModel>(info.col, info.pos, info.size);
		}
		if (info.type == FieldType::Ladder) {
			return std::make_shared<LadderModel>((info.col & collision::Up) != 0, info.pos, info.size);
		}
		if (info.type == FieldType::Penetrate) {
			return std::make_shared<PenetrateFloorModel>(info.pos, info.size, info.canDown);
		}
		return nullptr;
	}
}