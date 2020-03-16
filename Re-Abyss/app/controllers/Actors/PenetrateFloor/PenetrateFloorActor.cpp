#include "PenetrateFloorActor.hpp"

namespace abyss
{
	PenetrateFloorActor::PenetrateFloorActor(
		const s3d::Vec2& pos,
		const s3d::Vec2& size,
		bool canDown,
		ColDirection aroundFloor
	):
		FloorActor(ColDirection::Up, pos, size),
		m_canDown(canDown),
		m_aroundFloor(aroundFloor)
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
    bool PenetrateFloorActor::tryDown(const s3d::RectF& region) const
    {
		if (!m_canDown) {
			return false;
		}
		const auto& own = this->region();
		if (m_aroundFloor.isLeft() && own.x > region.x) {
			return false;
		}

		if (m_aroundFloor.isRight() && own.x + own.w < region.x + region.w) {
			return false;
		}
        return true;
    }
}
