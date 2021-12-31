#pragma once
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/Kind.hpp>
#include <Siv3D/Vector2D.hpp>
namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	struct BuildDesc
	{
		s3d::Vec2 offset{};
		double rotate{};
		double distOffset{};
		Kind kind{};
		double waitTimeSec{};
	};
}