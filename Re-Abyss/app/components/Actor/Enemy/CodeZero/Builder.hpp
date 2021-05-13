#pragma once
#include <abyss/commons/Fwd.hpp>
namespace abyss::Actor::Enemy
{
	struct CodeZeroEntity;
}
namespace abyss::Actor::Enemy::CodeZero
{
	struct Builder
	{
		static void Build(ActorObj*pActor, const CodeZeroEntity& entity);
	};
}