#include "EnemyTranslator.hpp"

#include <abyss/entities/Actors/Enemy/EnemyEntity.hpp>
#include <abyss/entities/Actors/Enemy/SlimeEntity.hpp>
#include <abyss/entities/Actors/Enemy/RollingTakoEntity.hpp>
#include <abyss/entities/Actors/Enemy/CaptainTakoEntity.hpp>
#include <abyss/entities/Actors/Enemy/IkalienEntity.hpp>
#include <abyss/entities/Actors/Enemy/LaunSharkEntity.hpp>
#include <abyss/entities/Actors/Enemy/SchieldEntity.hpp>

#include <abyss/entities/Actors/Enemy/CodeZeroEntity.hpp>

#include <abyss/controllers/Actors/Slime/SlimeActor.hpp>
#include <abyss/controllers/Actors/RollingTako/RollingTakoActor.hpp>
#include <abyss/controllers/Actors/CaptainTako/CaptainTakoActor.hpp>
#include <abyss/controllers/Actors/Ikalien/IkalienActor.hpp>
#include <abyss/controllers/Actors/LaunShark/LaunSharkActor.hpp>
#include <abyss/controllers/Actors/Schield/SchieldActor.hpp>

#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>

namespace abyss
{
    std::shared_ptr<EnemyActor> EnemyTranslator::ToActorPtr(const EnemyEntity& entity)
    {
#define CASE_ENEMY(type) case EnemyType::##type : return std::make_shared<type::type##Actor>(static_cast<const type##Entity&>(entity))

		switch (entity.type) {
			CASE_ENEMY(Slime);
			CASE_ENEMY(RollingTako);
			CASE_ENEMY(CaptainTako);
			CASE_ENEMY(Ikalien);
			CASE_ENEMY(LaunShark);
			CASE_ENEMY(Schield);
			CASE_ENEMY(CodeZero);
		default:
			break;
		}
		return nullptr;
#undef CASE_ENEMY
    }
}