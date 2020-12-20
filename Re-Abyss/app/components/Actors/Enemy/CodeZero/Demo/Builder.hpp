#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Enemy::CodeZero::Demo
{
	struct Builder
	{
		static void Build(IActor* pActor, const s3d::Vec2& pos);
	};
}