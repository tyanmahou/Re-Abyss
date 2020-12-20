#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	struct LaunSharkEntity;
}
namespace abyss::Actor::Enemy::LaunShark
{
	struct Builder
	{
		static void Build(IActor* pActor, const LaunSharkEntity& entity);
	};
}