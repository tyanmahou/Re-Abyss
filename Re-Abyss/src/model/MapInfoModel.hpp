#pragma once
#include<Siv3D/Vector2D.hpp>
#include"Collision.hpp"

namespace abyss
{
	enum class FieldType
	{
		None = 0x0,
		Floor = 0x1,
		Ladder = 0x2,
		Penetrate = 0x4,
	};

	struct MapInfoModel
	{
		FieldType type;
		s3d::Vec2 pos;
		s3d::Vec2 size;
		ColDirection col;
		bool canDown;
	};
}
