#pragma once
#include<Siv3D/Vector2D.hpp>
#include"../../application/util/Collision.hpp"

namespace abyss
{
	enum class MapType
	{
		None = 0x0,
		Floor = 0x1,
		Ladder = 0x2,
		Penetrate = 0x4,
	};

	struct MapEntity
	{
		MapType type;
		s3d::Vec2 pos;
		s3d::Vec2 size;
		ColDirection col;
		bool canDown;
	};
}
