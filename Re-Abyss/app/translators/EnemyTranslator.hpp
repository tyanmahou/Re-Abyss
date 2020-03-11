#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/actors/Enemy/EnemyActor.hpp>

namespace abyss
{
	class EnemyTranslator
	{
	public:
		static std::shared_ptr<EnemyActor> ToActorPtr(const EnemyEntity&);
	};
}
