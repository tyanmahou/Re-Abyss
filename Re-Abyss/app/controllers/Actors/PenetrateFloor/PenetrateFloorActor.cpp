#include "PenetrateFloorActor.hpp"

namespace abyss
{
	PenetrateFloorActor::PenetrateFloorActor(
		const s3d::Vec2& pos,
		const s3d::Vec2& size,
		bool canDown,
		ColDirection aroundFloor
	):
		MapActor(ColDirection::Up, pos - s3d::Vec2{ 0, 17.5 }, size - s3d::Vec2{0, 35}),
		m_canDown(canDown),
		m_aroundFloor(aroundFloor)
	{
		this->tag = U"penetrate_floor";
	}
	bool PenetrateFloorActor::canDown() const
	{
		return m_canDown;
	}
	bool PenetrateFloorActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
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
