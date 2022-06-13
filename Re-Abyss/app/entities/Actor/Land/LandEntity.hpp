#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/Collision/ColDirection.hpp>

namespace abyss::Actor::Land
{
	enum class LandType
	{
		None = 0x0,
		Floor = 0x1,
		Ladder = 0x2,
		Penetrate = 0x4,
	};

	struct LandEntity
	{
		s3d::uint32 id;
		s3d::uint32 gId;
        LandType type;
		s3d::Vec2 pos;
		s3d::Vec2 size;
		ColDirection col;
		ColDirection aroundFloor; // 周辺フロア情報
		bool canDown;
	};
}
