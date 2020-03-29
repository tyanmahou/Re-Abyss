#include "EnemyTranslator.hpp"

#include <abyss/entities/Enemy/EnemyEntity.hpp>
#include <abyss/entities/Enemy/RollingTakoEntity.hpp>
#include <abyss/controllers/Actors/Slime/SlimeActor.hpp>
#include <abyss/controllers/Actors/RollingTako/RollingTakoActor.hpp>

namespace abyss
{
    std::shared_ptr<EnemyActor> EnemyTranslator::ToActorPtr(const EnemyEntity& entity)
    {
		switch (entity.type) {
		case EnemyType::Slime:
			return std::make_shared<SlimeActor>(entity.pos);
		case EnemyType::RollingTako:
			return std::make_shared<RollingTakoActor>(static_cast<const RollingTakoEntity&>(entity));
		default:
			break;
		}
		return nullptr;
    }
}