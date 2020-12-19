#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
	struct SchieldEntity;
}

namespace abyss::Actor::Enemy::Schield
{
	struct Builder
	{
		static void Build(IActor* pActor, const SchieldEntity& entity);
	};
}