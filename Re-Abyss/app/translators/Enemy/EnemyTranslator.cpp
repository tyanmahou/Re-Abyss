#include "EnemyTranslator.hpp"

#include <abyss/entities/Actors/Enemy/EnemyEntity.hpp>
#include <abyss/entities/Actors/Enemy/SlimeEntity.hpp>
#include <abyss/entities/Actors/Enemy/RollingTakoEntity.hpp>
#include <abyss/entities/Actors/Enemy/CaptainTakoEntity.hpp>
#include <abyss/entities/Actors/Enemy/IkalienEntity.hpp>
#include <abyss/entities/Actors/Enemy/LaunSharkEntity.hpp>
#include <abyss/entities/Actors/Enemy/SchieldEntity.hpp>

#include <abyss/entities/Actors/Enemy/CodeZeroEntity.hpp>

#include <abyss/components/Actors/Enemy/RollingTako/Builder.hpp>
#include <abyss/components/Actors/Enemy/Schield/Builder.hpp>
#include <abyss/components/Actors/Enemy/Slime/Builder.hpp>

#include <abyss/controllers/World/World.hpp>

#include <abyss/controllers/Actors/Enemy/CaptainTako/CaptainTakoActor.hpp>
#include <abyss/controllers/Actors/Enemy/Ikalien/IkalienActor.hpp>
#include <abyss/controllers/Actors/Enemy/LaunShark/LaunSharkActor.hpp>

#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>

namespace abyss
{
    std::shared_ptr<Actor::Enemy::EnemyActor> EnemyTranslator::ToActorPtr(const EnemyEntity& entity)
    {
		using namespace Actor::Enemy;
#define CASE_ENEMY(type) case EnemyType::##type : return std::make_shared<type::type##Actor>(static_cast<const type##Entity&>(entity))

		switch (entity.type) {
			CASE_ENEMY(CaptainTako);
			CASE_ENEMY(Ikalien);
			CASE_ENEMY(LaunShark);
			CASE_ENEMY(CodeZero);
		default:
			break;
		}
		return nullptr;
#undef CASE_ENEMY
    }
	Ref<Actor::IActor> EnemyTranslator::buildActor(World& world, const EnemyEntity& entity)
	{
		using namespace Actor::Enemy;
#define CASE_ENEMY(type) case EnemyType::##type : return world.create<type::Builder>(static_cast<const type##Entity&>(entity))

		switch (entity.type) {
			CASE_ENEMY(RollingTako);
			CASE_ENEMY(Schield);
			CASE_ENEMY(Slime);
		default:
			break;
		}
		return nullptr;
#undef CASE_ENEMY
	}
}