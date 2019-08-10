#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
	struct Physics
	{
		s3d::Vec2 pos;
		s3d::Vec2 vellocity;
		s3d::Vec2 accel;
	};
}