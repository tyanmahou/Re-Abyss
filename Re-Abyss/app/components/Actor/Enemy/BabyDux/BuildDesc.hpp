#pragma once
#include <Siv3D/Vector2D.hpp>
namespace abyss::Actor::Enemy::BabyDux
{
	struct BuildDesc
	{
		s3d::Vec2 posOffset{};
		double appearTime{ 2.0 };
		s3d::Vec2 appearMove{};
	};
}
