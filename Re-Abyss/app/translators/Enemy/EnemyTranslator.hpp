#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>

namespace abyss
{
	class EnemyTranslator
	{
	public:
		static std::shared_ptr<Actor::Enemy::EnemyActor> ToActorPtr(const EnemyEntity&);
	};
}
