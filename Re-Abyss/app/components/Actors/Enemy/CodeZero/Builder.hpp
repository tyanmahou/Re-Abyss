#pragma once
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
	struct CodeZeroEntity;
}
namespace abyss::Actor::Enemy::CodeZero
{
	struct Builder
	{
		static void Build(IActor*pActor, const CodeZeroEntity& entity);
	};
}