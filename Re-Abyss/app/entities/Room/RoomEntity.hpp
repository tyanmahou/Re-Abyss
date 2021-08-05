#pragma once
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Color.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss
{
	struct RoomEntity
	{
		s3d::uint32 roomId;
		s3d::RectF region;
		s3d::uint8 passbleBits;
		s3d::Optional<s3d::ColorF> lightColor;
	};
}