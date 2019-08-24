#include "PenetrateFloorModel.hpp"

namespace abyss
{
	PenetrateFloorModel::PenetrateFloorModel(const s3d::Vec2& pos, const s3d::Vec2& size, bool canDown):
		FloorModel(collision::Up, pos, size),
		m_canDown(canDown)
	{
		this->tag = L"penetrate_floor";
	}
	bool PenetrateFloorModel::canDown() const
	{
		return m_canDown;
	}
}
