#include "MapTranslator.hpp"
#include "../../data/entity/MapEntity.hpp"

#include "../model/object/PenetrateFloorModel.hpp"
#include "../model/object/LadderModel.hpp"

namespace abyss
{
	std::shared_ptr<MapModel> MapTranslator::create(const MapEntity& entity)
	{
		if (entity.type == MapType::Floor) {
			return std::make_shared<FloorModel>(entity.col, entity.pos, entity.size);
		}
		if (entity.type == MapType::Ladder) {
			return std::make_shared<LadderModel>(entity.col, entity.pos, entity.size);
		}
		if (entity.type == MapType::Penetrate) {
			return std::make_shared<PenetrateFloorModel>(entity.pos, entity.size, entity.canDown);
		}
		return nullptr;
	}
}