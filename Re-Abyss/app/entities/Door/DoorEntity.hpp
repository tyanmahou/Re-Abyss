#pragma once
#include<Siv3D/Vector2D.hpp>

namespace abyss
{
	struct DoorEntity
	{
		s3d::Vec2 pos;
		s3d::Vec2 targetPos;
		s3d::Vec2 size;
	};
}
