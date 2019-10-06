#include "PenetrateFloorModel.hpp"
#include <domain/visitor/WorldVisitor.hpp>
namespace abyss
{
	PenetrateFloorModel::PenetrateFloorModel(const s3d::Vec2& pos, const s3d::Vec2& size, bool canDown):
		FloorModel(collision::Up, pos, size),
		m_canDown(canDown)
	{
		this->tag = U"penetrate_floor";
	}
	bool PenetrateFloorModel::canDown() const
	{
		return m_canDown;
	}
	void PenetrateFloorModel::accept(const WorldVisitor& visitor)
	{
		visitor.visit(*this);
	}
}
