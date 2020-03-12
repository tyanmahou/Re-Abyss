#pragma once
#include "Forward.hpp"

#include <Siv3D/Vector2D.hpp>

namespace abyss
{
	// TODO model側にうつしたい
	struct Physics
	{
		s3d::Vec2 pos;
		s3d::Vec2 vellocity;
		s3d::Vec2 accel;
		Forward forward;

		Physics():
			pos(0,0),
			vellocity(0,0),
			accel(0,0),
			forward(Forward::None)
		{}
	};
}