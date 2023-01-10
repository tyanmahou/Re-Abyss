#include <abyss/translators/Actor/Land/LandTranslator.hpp>

#include <abyss/entities/Actor/Land/LandEntity.hpp>
#include <abyss/components/Actor/Land/Floor/Builder.hpp>
#include <abyss/components/Actor/Land/PenetrateFloor/Builder.hpp>
#include <abyss/components/Actor/Land/Ladder/Builder.hpp>

#include <abyss/modules/Actor/Actors.hpp>

namespace abyss::Actor::Land
{
	Ref<Actor::ActorObj> LandTranslator::buildActor(Actors& actors, const LandEntity& entity)
	{
		using namespace Actor::Land;
		if (entity.type == LandType::Floor) {
			return actors.create<Floor::Builder>(entity.col, entity.pos, entity.size);
		}
		if (entity.type == LandType::Ladder) {
			return actors.create<Ladder::Builder>(entity.col, entity.pos, entity.size);
		}
		if (entity.type == LandType::Penetrate) {
			return actors.create<PenetrateFloor::Builder>(entity.pos, entity.size, entity.canDown, entity.aroundFloor);
		}
		return nullptr;
	}
}
