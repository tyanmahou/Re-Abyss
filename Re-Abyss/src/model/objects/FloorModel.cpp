#include "FloorModel.hpp"

#include <Siv3D.hpp>

namespace abyss
{
	FloorModel::FloorModel(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size):
		m_col(col),
		m_pos(pos),
		m_size(size)
	{
		this->tag = L"floor";
	}
	s3d::Shape FloorModel::getCollider() const
	{
		return static_cast<Shape>(RectF(m_pos - m_size/2, m_size));
	}
	s3d::RectF FloorModel::region() const
	{
		return RectF{ m_pos - m_size / 2, m_size };
	}
	ColDirection FloorModel::getCol() const
	{
		return m_col;
	}
}