#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy
{
	class EnemyTranslator
	{
	public:
		Ref<Actor::ActorObj> buildActor(World& world, const EnemyEntity& entity);
	};
}
