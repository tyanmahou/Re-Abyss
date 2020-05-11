#include "MapTranslator.hpp"
#include <abyss/entities/Actors/Map/MapEntity.hpp>
#include <abyss/controllers/Actors/Map/Floor/FloorActor.hpp>
#include <abyss/controllers/Actors/Map/PenetrateFloor/PenetrateFloorActor.hpp>
#include <abyss/controllers/Actors/Map/Ladder/LadderActor.hpp>

namespace abyss
{
	std::shared_ptr<MapActor> MapTranslator::ToActorPtr(const MapEntity& entity)
	{
		if (entity.type == MapType::Floor) {
			return std::make_shared<Floor::FloorActor>(entity.col, entity.pos, entity.size);
		}
		if (entity.type == MapType::Ladder) {
			return std::make_shared<Ladder::LadderActor>(entity.col, entity.pos, entity.size);
		}
		if (entity.type == MapType::Penetrate) {
			return std::make_shared<PenetrateFloor::PenetrateFloorActor>(entity.pos, entity.size, entity.canDown, entity.aroundFloor);
		}
		return nullptr;
	}
}