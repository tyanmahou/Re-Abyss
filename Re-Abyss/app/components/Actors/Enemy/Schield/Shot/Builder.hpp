#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Actor::Enemy::Schield::Shot
{
	struct Builder
	{
		static void Build(IActor* pActor, const s3d::Vec2& pos, const s3d::Vec2& dir);
	};
}