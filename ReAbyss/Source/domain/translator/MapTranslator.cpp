#include "MapTranslator.hpp"
#include <data/entity/MapEntity.hpp>

#include <domain/actor/PenetrateFloorActor.hpp>
#include <domain/actor/LadderActor.hpp>

namespace abyss
{
	std::shared_ptr<MapActor> MapTranslator::create(const MapEntity& entity)
	{
		if (entity.type == MapType::Floor) {
			return std::make_shared<FloorActor>(entity.col, entity.pos, entity.size);
		}
		if (entity.type == MapType::Ladder) {
			return std::make_shared<LadderActor>(entity.col, entity.pos, entity.size);
		}
		if (entity.type == MapType::Penetrate) {
			return std::make_shared<PenetrateFloorActor>(entity.pos, entity.size, entity.canDown);
		}
		return nullptr;
	}
}