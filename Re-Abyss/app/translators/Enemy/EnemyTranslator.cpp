#include "EnemyTranslator.hpp"
#include <data/entity/EnemyEntity.hpp>
#include <domain/actor/EnemyActor.hpp>
#include <domain/actor/SlimeActor.hpp>
namespace abyss
{
	std::shared_ptr<EnemyActor> EnemyTranslator::create(const EnemyEntity& entity)
	{
		switch (entity.type)
		{
		case EnemyType::Slime:
			return std::make_shared<SlimeActor>(entity.pos);
		default:
			break;
		}
		return nullptr;
	}
}