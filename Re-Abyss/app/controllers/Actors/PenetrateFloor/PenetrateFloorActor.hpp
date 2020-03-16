#pragma once

#include <abyss/controllers/Actors/Floor/FloorActor.hpp>

namespace abyss
{
	class PenetrateFloorActor : public FloorActor
	{
		bool m_canDown;
		ColDirection m_aroundFloor;
	public:
		PenetrateFloorActor(const s3d::Vec2& pos, const s3d::Vec2& size, bool canDown, ColDirection aroundFloor);
		bool canDown() const;
		void accept(const ActVisitor& visitor) override;

		bool tryDown(const s3d::RectF& region) const;
	};
}