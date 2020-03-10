﻿#include "EnemyTranslator.hpp"

#include <abyss/entities/EnemyEntity.hpp>
#include <abyss/models/actors/Slime/SlimeActor.hpp>

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