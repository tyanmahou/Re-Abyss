#pragma once

#include "FloorModel.hpp"

namespace abyss
{
	class PenetrateFloorModel : public FloorModel
	{
		bool m_canDown;
	public:
		PenetrateFloorModel(const s3d::Vec2& pos, const s3d::Vec2& size, bool canDown);
		bool canDown() const;
		void accept(const WorldVisitor& visitor) override;
	};
}