#pragma once
#include <memory>

namespace abyss
{
	class EnemyModel;
	struct EnemyEntity;

	class EnemyTranslator
	{
	public:
		EnemyTranslator() = default;
		std::shared_ptr<EnemyModel> create(const EnemyEntity&);
	};
}
