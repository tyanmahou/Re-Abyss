#include "MapTranslator.hpp"
#include <abyss/entities/MapEntity.hpp>

#include <abyss/controllers/Actors/PenetrateFloor/PenetrateFloorActor.hpp>
#include <abyss/controllers/Actors/Ladder/LadderActor.hpp>

namespace abyss
{
	std::shared_ptr<MapActor> MapTranslator::ToActorPtr(const MapEntity& entity)
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