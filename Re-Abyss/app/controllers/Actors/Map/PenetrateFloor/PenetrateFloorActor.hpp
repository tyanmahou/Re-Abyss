#pragma once

#include <abyss/controllers/Actors/Map/MapActor.hpp>

namespace abyss::PenetrateFloor
{
	class PenetrateFloorActor : public MapActor
	{
		bool m_canDown;
		ColDirection m_aroundFloor;
	public:
		PenetrateFloorActor(const s3d::Vec2& pos, const s3d::Vec2& size, bool canDown, ColDirection aroundFloor);
		bool canDown() const;
		bool accept(const ActVisitor& visitor) override;

		bool tryDown(const s3d::RectF& region) const;
	};
}