#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
	class EnemyTranslator
	{
	public:
		Ref<Actor::ActorObj> buildActor(World& world, const EnemyEntity& entity);
	};
}
