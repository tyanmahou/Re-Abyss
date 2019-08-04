#pragma once
#include <Siv3D/Rectangle.hpp>

namespace s3dTiled
{
	struct TiledObject;
}
namespace abyss
{
	enum class Forward
	{
		Up = 0x1,
		Down = 0x2,
		Left = 0x4,
		Right = 0x8,
	};

	struct RoomBorders
	{
		double up = 0, down = 0, left = 0, right = 0;
	};
	class Room
	{
		s3d::RectF m_region;
		s3d::uint8 m_passbleBits;
	public:
		Room() = default;
		Room(const s3dTiled::TiledObject& obj);

		bool passable(Forward f) const;
		double pos(Forward f) const;
		const s3d::RectF& getRegion()const;

		operator s3d::RectF() const;

		RoomBorders cameraBorders()const ;
		s3d::Vec2 cameraBorderAdjusted(s3d::Vec2 pos)const;

		RoomBorders borders()const;
		s3d::Vec2 borderAdjusted(s3d::Vec2 pos) const;
	};
}