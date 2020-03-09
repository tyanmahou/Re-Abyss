#pragma once
#include <memory>

namespace abyss
{
	class EnemyActor;
	struct EnemyEntity;

	class EnemyTranslator
	{
	public:
		EnemyTranslator() = default;
		std::shared_ptr<EnemyActor> create(const EnemyEntity&);
	};
}
