#pragma once
#include <Siv3D/Rectangle.hpp>

namespace abyss
{
	struct RoomEntity
	{
		s3d::uint32 roomId;
		s3d::RectF region;
		s3d::uint8 passbleBits;
	};
}