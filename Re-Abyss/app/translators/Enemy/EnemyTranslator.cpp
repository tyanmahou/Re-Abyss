#include "EnemyTranslator.hpp"

#include <abyss/entities/Enemy/EnemyEntity.hpp>
#include <abyss/entities/Enemy/SlimeEntity.hpp>
#include <abyss/entities/Enemy/RollingTakoEntity.hpp>
#include <abyss/entities/Enemy/CaptainTakoEntity.hpp>
#include <abyss/entities/Enemy/IkalienEntity.hpp>
#include <abyss/entities/Enemy/LaunSharkEntity.hpp>

#include <abyss/controllers/Actors/Slime/SlimeActor.hpp>
#include <abyss/controllers/Actors/RollingTako/RollingTakoActor.hpp>
#include <abyss/controllers/Actors/CaptainTako/CaptainTakoActor.hpp>
#include <abyss/controllers/Actors/Ikalien/IkalienActor.hpp>
#include <abyss/controllers/Actors/LaunShark/LaunSharkActor.hpp>

namespace abyss
{
    std::shared_ptr<EnemyActor> EnemyTranslator::ToActorPtr(const EnemyEntity& entity)
    {
#define CASE_ENEMY(type) case EnemyType::##type : return std::make_shared<type##Actor>(static_cast<const type##Entity&>(entity))

		switch (entity.type) {
			CASE_ENEMY(Slime);
			CASE_ENEMY(RollingTako);
			CASE_ENEMY(CaptainTako);
			CASE_ENEMY(Ikalien);
			CASE_ENEMY(LaunShark);
		default:
			break;
		}
		return nullptr;
#undef CASE_ENEMY
    }
}