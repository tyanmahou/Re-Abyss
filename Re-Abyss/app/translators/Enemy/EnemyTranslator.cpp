#include "EnemyTranslator.hpp"

#include <abyss/entities/Actor/Enemy/EnemyEntity.hpp>
#include <abyss/entities/Actor/Enemy/SlimeEntity.hpp>
#include <abyss/entities/Actor/Enemy/RollingTakoEntity.hpp>
#include <abyss/entities/Actor/Enemy/CaptainTakoEntity.hpp>
#include <abyss/entities/Actor/Enemy/IkalienEntity.hpp>
#include <abyss/entities/Actor/Enemy/LaunSharkEntity.hpp>
#include <abyss/entities/Actor/Enemy/SchieldEntity.hpp>

#include <abyss/entities/Actor/Enemy/CodeZeroEntity.hpp>

#include <abyss/components/Actor/Enemy/CaptainTako/Builder.hpp>
#include <abyss/components/Actor/Enemy/Ikalien/Builder.hpp>
#include <abyss/components/Actor/Enemy/LaunShark/Builder.hpp>
#include <abyss/components/Actor/Enemy/RollingTako/Builder.hpp>
#include <abyss/components/Actor/Enemy/Schield/Builder.hpp>
#include <abyss/components/Actor/Enemy/Slime/Builder.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/Builder.hpp>

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