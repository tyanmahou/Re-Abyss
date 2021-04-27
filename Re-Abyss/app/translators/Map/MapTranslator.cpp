#include "MapTranslator.hpp"
#include <abyss/entities/Actor/Map/MapEntity.hpp>
#include <abyss/components/Actor/Map/Floor/Builder.hpp>
#include <abyss/components/Actor/Map/PenetrateFloor/Builder.hpp>
#include <abyss/components/Actor/Map/Ladder/Builder.hpp>

#include <abyss/modules/World/World.hpp>

namespace abyss
{
	Ref<Actor::ActorObj> MapTranslator::buildActor(World& world, const MapEntity& entity)
	{
		using namespace Actor::Map;
		if (entity.type == MapType::Floor) {
			return world.create<Floor::Builder>(entity.col, entity.pos, entity.size);
		}
		if (entity.type == MapType::Ladder) {
			return world.create<Ladder::Builder>(entity.col, entity.pos, entity.size);
		}
		if (entity.type == MapType::Penetrate) {
			return world.create<PenetrateFloor::Builder>(entity.pos, entity.size, entity.canDown, entity.aroundFloor);
		}
		return nullptr;
	}
}