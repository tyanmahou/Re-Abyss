#include "PenetrateFloorActor.hpp"

namespace abyss
{
	PenetrateFloorActor::PenetrateFloorActor(const s3d::Vec2& pos, const s3d::Vec2& size, bool canDown):
		FloorActor(collision::Up, pos, size),
		m_canDown(canDown)
	{
		this->tag = U"penetrate_floor";
	}
	bool PenetrateFloorActor::canDown() const
	{
		return m_canDown;
	}
	void PenetrateFloorActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}
}
