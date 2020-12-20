#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	struct IkalienEntity;
}
namespace abyss::Actor::Enemy::Ikalien
{
	struct Builder
	{
		static void Build(IActor* pActor, const IkalienEntity& entity);
	};
}