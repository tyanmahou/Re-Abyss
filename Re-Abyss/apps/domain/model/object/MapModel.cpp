#include "MapModel.hpp"

namespace abyss
{
	MapModel::MapModel(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size) :
		m_col(col),
		m_pos(pos),
		m_size(size)
	{}

	const s3d::Vec2& MapModel::getPos() const
	{
		return m_pos;
	}

	ColDirection MapModel::getCol() const
	{
		return m_col;
	}

	s3d::RectF MapModel::region() const
	{
		return s3d::RectF{ m_pos - m_size / 2, m_size };
	}

	s3d::Shape MapModel::getCollider() const
	{
		return static_cast<s3d::Shape>(this->region());
	}
}