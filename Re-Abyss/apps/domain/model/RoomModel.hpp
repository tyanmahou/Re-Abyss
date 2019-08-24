#pragma once
#include <Siv3D/Rectangle.hpp>
#include "../../application/types/Forward.hpp"

namespace abyss
{
	struct RoomBorders
	{
		double up = 0, down = 0, left = 0, right = 0;
	};
	class RoomModel
	{
		s3d::RectF m_region;
		s3d::uint8 m_passbleBits;
	public:
		RoomModel() = default;
		RoomModel(const s3d::RectF& region, s3d::uint8 passbleBits);

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