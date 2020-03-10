#include "EnemyTranslator.hpp"

#include <abyss/entities/EnemyEntity.hpp>
#include <abyss/translators/Slime/SlimeTranslator.hpp>

namespace abyss
{
    std::shared_ptr<EnemyActor> EnemyTranslator::ToActorPtr(const EnemyEntity& entity)
    {
		switch (entity.type) {
		case EnemyType::Slime:
			return SlimeTranslator::ToActorPtr(entity);
		default:
			break;
		}
		return nullptr;
    }
}