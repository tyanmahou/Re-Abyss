#pragma once
#include <Siv3D/Rectangle.hpp>

namespace abyss
{
	struct RoomEntity
	{
		s3d::RectF m_region;
		s3d::uint8 m_passbleBits;
	};
}