#include "EnemyTranslator.hpp"
#include <data/entity/EnemyEntity.hpp>
#include <domain/model/object/EnemyModel.hpp>
#include <domain/model/object/SlimeModel.hpp>
namespace abyss
{
	std::shared_ptr<EnemyModel> EnemyTranslator::create(const EnemyEntity& entity)
	{
		switch (entity.type)
		{
		case EnemyType::Slime:
			return std::make_shared<SlimeModel>(entity.pos);
		default:
			break;
		}
		return nullptr;
	}
}