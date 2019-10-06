#include "LadderActor.hpp"
#include <Siv3D.hpp>

namespace abyss
{
	LadderActor::LadderActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size):
		MapActor(col, pos, size)
	{
		this->tag = U"ladder";
	}

	s3d::Line LadderActor::getCenterLine() const
	{
		Vec2 beginY = m_pos - Vec2{ 0, m_size.y/2.0 + 1.0 };
		Vec2 endY = m_pos + Vec2{ 0, m_size.y / 2.0 - 10.0};
		return s3d::Line(beginY, endY);
	}
	bool LadderActor::isTop() const
	{
		return (m_col & collision::Up) != 0;
	}
	void LadderActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}
}