#include "EnemyTranslator.hpp"

#include <abyss/entities/Enemy/EnemyEntity.hpp>
#include <abyss/controllers/Actors/Slime/SlimeActor.hpp>

namespace abyss
{
    std::shared_ptr<EnemyActor> EnemyTranslator::ToActorPtr(const EnemyEntity& entity)
    {
		switch (entity.type) {
		case EnemyType::Slime:
			return std::make_shared<SlimeActor>(entity.pos);
		default:
			break;
		}
		return nullptr;
    }
}