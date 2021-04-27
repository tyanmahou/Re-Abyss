#include "EnemyTranslator.hpp"

#include <abyss/entities/Actors/Enemy/EnemyEntity.hpp>
#include <abyss/entities/Actors/Enemy/SlimeEntity.hpp>
#include <abyss/entities/Actors/Enemy/RollingTakoEntity.hpp>
#include <abyss/entities/Actors/Enemy/CaptainTakoEntity.hpp>
#include <abyss/entities/Actors/Enemy/IkalienEntity.hpp>
#include <abyss/entities/Actors/Enemy/LaunSharkEntity.hpp>
#include <abyss/entities/Actors/Enemy/SchieldEntity.hpp>

#include <abyss/entities/Actors/Enemy/CodeZeroEntity.hpp>

#include <abyss/components/Actors/Enemy/CaptainTako/Builder.hpp>
#include <abyss/components/Actors/Enemy/Ikalien/Builder.hpp>
#include <abyss/components/Actors/Enemy/LaunShark/Builder.hpp>
#include <abyss/components/Actors/Enemy/RollingTako/Builder.hpp>
#include <abyss/components/Actors/Enemy/Schield/Builder.hpp>
#include <abyss/components/Actors/Enemy/Slime/Builder.hpp>

#include <abyss/components/Actors/Enemy/CodeZero/Builder.hpp>

#include <abyss/modules/World/World.hpp>

namespace abyss
{
	Ref<Actor::ActorObj> EnemyTranslator::buildActor(World& world, const EnemyEntity& entity)
	{
		using namespace Actor::Enemy;
#define CASE_ENEMY(type) case EnemyType::##type : return world.create<type::Builder>(static_cast<const type##Entity&>(entity))

		switch (entity.type) {
			CASE_ENEMY(CaptainTako);
			CASE_ENEMY(Ikalien);
			CASE_ENEMY(LaunShark);
			CASE_ENEMY(RollingTako);
			CASE_ENEMY(Schield);
			CASE_ENEMY(Slime);

			CASE_ENEMY(CodeZero);
		default:
			break;
		}
		return nullptr;
#undef CASE_ENEMY
	}
}