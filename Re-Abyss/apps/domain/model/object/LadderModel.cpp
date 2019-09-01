#include "LadderModel.hpp"
#include <Siv3D.hpp>

namespace abyss
{
	LadderModel::LadderModel(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size):
		MapModel(col, pos, size)
	{
		this->tag = L"ladder";
	}

	s3d::Line LadderModel::getCenterLine() const
	{
		Vec2 beginY = m_pos - Vec2{ 0, m_size.y/2.0 + 1.0 };
		Vec2 endY = m_pos + Vec2{ 0, m_size.y / 2.0 - 10.0};
		return s3d::Line(beginY, endY);
	}
	bool LadderModel::isTop() const
	{
		return (m_col & collision::Up) != 0;
	}
	void LadderModel::accept(const WorldVisitor& visitor)
	{
		visitor.visit(*this);
	}
}