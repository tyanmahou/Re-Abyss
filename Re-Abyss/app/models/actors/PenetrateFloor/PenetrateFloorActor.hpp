#pragma once

#include <abyss/models/actors/Floor/FloorActor.hpp>

namespace abyss
{
	class PenetrateFloorActor : public FloorActor
	{
		bool m_canDown;
	public:
		PenetrateFloorActor(const s3d::Vec2& pos, const s3d::Vec2& size, bool canDown);
		bool canDown() const;
		void accept(const ActVisitor& visitor) override;
	};
}